// Copyright @ MyScript. All rights reserved.

#include <FontMetricsProvider.h>

#include <QtGui/QTextLayout>
#include <QtGui/QFontMetricsF>
#include <QtGui/QFontInfo>
#include <QtGui/QPainterPath>
#include <QtGui/QScreen>
#include <QtWidgets/QApplication>
#include <QtCore/QDir>

#include <cassert>

using namespace myscript::iink::graphics;
using namespace myscript::iink::text;
using namespace myscript::iink::uireferenceimplementation;

namespace
{
  class FontFamilies
  {
  public:
      static const std::string DefaultFamily;
      static const std::string DefaultStixFamily;

      static std::string MyScriptInter;
      static std::string MyScriptInterBold;
      static std::string StixRegular;
      static std::string StixItalic;

  public:
      static void initialize()
      {
        if (initialized)
            return;

        const bool useResources = true;
        MyScriptInter = registerFontFamily("MyScriptInter-Regular.otf", "MyScriptInter", FontFamilies::DefaultFamily, useResources);
        MyScriptInterBold = registerFontFamily("MyScriptInter-Bold.otf", "MyScriptInter", FontFamilies::DefaultFamily, useResources);
        StixRegular = registerFontFamily("STIXGeneral.ttf", "STIXGeneral", FontFamilies::DefaultStixFamily, useResources);
        StixItalic = registerFontFamily("STIX-Italic.otf", "STIX", FontFamilies::DefaultStixFamily, useResources);

        initialized = true;
      }

  private:
      FontFamilies() = delete;

      static std::string registerFontFamily(const std::string& filename, const std::string&name, const std::string& defaultFamily, bool fromResources)
      {
        int id = -1;

        if (fromResources)
        {
          // Fonts are packaged into the QT resources
          auto fontFolder = QDir(":/" + QString::fromStdString(FontFamilies::FontFolder));
//            auto fontFolder = QDir("D:\\work\\fonts");

          auto rscPath = fontFolder.filePath(QString::fromStdString(filename));
          id = QFontDatabase::addApplicationFont(rscPath);
        }
        else
        {
          // Fonts are in the "fonts" subfolder of the working directory
          auto fontFolder = QDir(QString::fromStdString(FontFamilies::FontFolder));
          auto localPath = fontFolder.filePath(QString::fromStdString(filename));
          auto fullPath = QFileInfo(localPath).absoluteFilePath();
          if (QFile::exists(fullPath))
            id = QFontDatabase::addApplicationFont(fullPath);
        }

        if (id >= 0)
        {
          auto families = QFontDatabase::applicationFontFamilies(id);
          for (const QString& f : families)
          {
            if (f == QString::fromStdString(name))
              return name;
          }
        }

        return defaultFamily;
      }

  private:
      static const std::string FontFolder;
      static bool initialized;
  };

  const std::string FontFamilies::DefaultFamily = "Segoe UI";
  const std::string FontFamilies::DefaultStixFamily = "STIX";

  const std::string FontFamilies::FontFolder = "fonts";

  bool FontFamilies::initialized = false;

  std::string FontFamilies::MyScriptInter;
  std::string FontFamilies::MyScriptInterBold;
  std::string FontFamilies::StixRegular;
  std::string FontFamilies::StixItalic;
}


void FontMetricsProvider::initialize()
{
  FontFamilies::initialize();
}

float FontMetricsProvider::px2mm(float px, float dpi)
{
  return 25.4f * (px / dpi);
}

float FontMetricsProvider::mm2px(float mmm, float dpi)
{
  return (mmm / 25.4f) * dpi;
}

std::vector<Rectangle> FontMetricsProvider::getCharacterBoundingBoxes(std::shared_ptr<Text> text, const std::vector<TextSpan>& spans)
{
  std::vector<GlyphMetrics> result_ = getGlyphMetrics(text, spans);

  std::vector<Rectangle> result;
  for (const auto& metrics : result_)
    result.push_back(metrics.boundingBox);

  return result;
}

float FontMetricsProvider::getFontSizePx(const Style& style) noexcept
{
  return style.getFontSize();
}

std::unordered_map<std::string, GlyphMetrics>& FontMetricsProvider::getFontCache(const QFont& font)
{
  QFontInfo fontInfo(font);
  std::string family = fontInfo.family().toUtf8().toStdString();
  float size = fontInfo.pointSizeF();
  int weight = fontInfo.weight();
  bool italic = fontInfo.italic();
  FontKey key = { family, size, weight, italic };
  auto itr = cache.find(key);
  if (itr == cache.end())
    itr = cache.insert(itr, std::make_pair(key, std::unordered_map<std::string, GlyphMetrics>()));
  return itr->second;
}

const GlyphMetrics& FontMetricsProvider::getGlyphMetrics(std::unordered_map<std::string, GlyphMetrics>& fontCache, const QFont& font, const std::string& glyph, float dpiX, float dpiY)
{
  auto itr = fontCache.find(glyph);
  if (itr == fontCache.end())
  {
    QFontMetricsF fontMetrics(font);

    QString glyph_ = QString::fromStdString(glyph);

    QPainterPath tempPainterPath;
    tempPainterPath.addText(0, 0, font, glyph_);
    QRectF r_ = tempPainterPath.boundingRect();

    if (r_.width() == 0)
    {
      r_ = fontMetrics.boundingRect(glyph_);
    }

    GlyphMetrics glyphMetrics;
    glyphMetrics.boundingBox.x = px2mm(r_.x(), dpiX);
    glyphMetrics.boundingBox.y = px2mm(r_.y(), dpiY);
    glyphMetrics.boundingBox.width = px2mm(r_.width(), dpiX);
    glyphMetrics.boundingBox.height = px2mm(r_.height(), dpiY);

    glyphMetrics.leftSideBearing = -glyphMetrics.boundingBox.x;
#if QT_VERSION >= QT_VERSION_CHECK(5, 11, 0)
    float adv = fontMetrics.horizontalAdvance(glyph_);
    float right = px2mm(adv, dpiX);
    glyphMetrics.rightSideBearing = right - (glyphMetrics.boundingBox.x + glyphMetrics.boundingBox.width);
#else
    glyphMetrics.rightSideBearing = 0;
#endif

    itr = fontCache.insert(itr, std::make_pair(glyph, glyphMetrics));
  }
  return itr->second;
}

std::vector<GlyphMetrics> FontMetricsProvider::getGlyphMetrics(std::shared_ptr<Text> text, const std::vector<TextSpan>& spans)
{
  std::vector<GlyphMetrics> result;
  float dpiX = (float)QApplication::screens().at(0)->physicalDotsPerInchX();
  float dpiY = (float)QApplication::screens().at(0)->physicalDotsPerInchY();

  QVector<QTextLayout::FormatRange> formats;

  // first pass: compute intrinsic glyph metrics
  for (int i = 0; i < spans.size(); ++i)
  {
    const TextSpan textSpan = spans[i];
    const Style style = textSpan.getStyle();

    std::string family_ = toPlatformFontFamily(style.getFontFamily(), style.getFontStyle(), style.getFontWeight());
    int size_ = (int)std::round(mm2px(style.getFontSize(), dpiY));
    auto weight_ = toPlatformFontWeight(style.getFontWeight());
    auto style_ = toPlatformFontStyle(style.getFontStyle());

    QFont font(QString::fromStdString(family_));
    font.setPixelSize(size_);
    font.setWeight(weight_);
    font.setStyle(style_);

    QFontMetrics fontMetrics(font);

    auto& fontCache = getFontCache(font);

    int begin = spans[i].getBeginPosition();
    int end = spans[i].getEndPosition();

    for (int j = begin; j < end; ++j)
    {
      std::string glyph = text->getGlyphLabelAt(j);
      GlyphMetrics glyphMetrics = getGlyphMetrics(fontCache, font, glyph, dpiX, dpiY);
      result.push_back(glyphMetrics);
    }

    QTextLayout::FormatRange range;
    range.format.setFont(font);
    range.start = begin;
    range.length = end - begin;

    formats.append(range);
  }

  // second pass: layout the text => position the glyphs
  if (text->getGlyphCount() > 1)
  {
    QTextLayout textLayout(QString::fromStdString(text->getLabel()));
    textLayout.setFormats(formats);
    textLayout.beginLayout();
    QTextLine line = textLayout.createLine();
    line.setPosition(QPointF(0, 0));
    textLayout.endLayout();

    assert(textLayout.lineCount() == 1);

    for (int i = 0; i < text->getGlyphCount(); ++i)
    {
      int begin = text->getGlyphUtf16BeginAt(i);
      int end = text->getGlyphUtf16EndAt(i);
      QList<QGlyphRun> runs = textLayout.glyphRuns(begin, end - begin);
      QGlyphRun run = runs[0];
      QRectF box = run.boundingRect();
      float pos = px2mm(box.x(), dpiX);
      result[i].boundingBox.x += pos;
    }
  }

  return result;
}

std::string FontMetricsProvider::toPlatformFontFamily(const std::string& family, const std::string& style, int weight)
{
  auto family_ = family;

  if (family == "MyScriptInter")
    family_ = (toPlatformFontWeight(weight) == QFont::Bold) ? FontFamilies::MyScriptInterBold : FontFamilies::MyScriptInter;
  else if (family == "STIX")
    family_ = (toPlatformFontStyle(style) == QFont::Style::StyleItalic) ? FontFamilies::StixItalic : FontFamilies::StixRegular;

  if (family_.empty())
    family_ = FontFamilies::DefaultFamily;

#if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
  if (!QFontDatabase().hasFamily(QString::fromStdString(family_)))
    family_ = FontFamilies::DefaultFamily;
#endif

  return family_;
}

QFont::Weight FontMetricsProvider::toPlatformFontWeight(int weight)
{
  if (weight >= 700)
    return QFont::Bold;
  else if (weight >= 400)
    return QFont::Normal;
  else
    return QFont::Light;
}

QFont::Style FontMetricsProvider::toPlatformFontStyle(const std::string& style)
{
  auto fontStyle = QFont::Style::StyleNormal;
  if (style == "italic")
    fontStyle = QFont::Style::StyleItalic;
  else if (style == "oblique")
    fontStyle = QFont::Style::StyleOblique;

  return fontStyle;
}

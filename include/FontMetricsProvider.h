// Copyright @ MyScript. All rights reserved.

#pragma once

#include <iink/text/IFontMetricsProvider.h>
#include <QtGui/QFont>
#include <utility>
#include <unordered_map>

namespace myscript {
namespace iink {
namespace uireferenceimplementation {

struct FontKey
{
  std::string family;
  float size;
  int weight;
  bool italic;

  bool operator == (const FontKey& rhs) const
  {
    return family == rhs.family && size == rhs.size && weight == rhs.weight && italic == rhs.italic;
  }
};

} // end of: namespace uireferenceimplementation
} // end of: namespace iink
} // end of: namespace myscript

namespace std {

  template <>
  struct hash<myscript::iink::uireferenceimplementation::FontKey>/* : public unary_function<myscript::iink::uireferenceimplementation::FontKey, size_t>*/
  {
    size_t operator()(const myscript::iink::uireferenceimplementation::FontKey& value) const noexcept
    {
      return std::hash<std::string>()(value.family) ^ std::hash<float>()(value.size) ^ std::hash<int>()(value.weight) ^ std::hash<bool>()(value.italic);
    }
  };

} // end of: namespace std

namespace myscript {
namespace iink {
namespace uireferenceimplementation {

class FontMetricsProvider : public text::IFontMetricsProvider
{
public:
  static void initialize();

  FontMetricsProvider() = default;
  virtual ~FontMetricsProvider() = default;

  virtual std::vector<graphics::Rectangle> getCharacterBoundingBoxes(std::shared_ptr<text::Text> text, const std::vector<text::TextSpan>& spans) override;
  virtual float getFontSizePx(const graphics::Style& style) noexcept override;

  virtual bool supportsGlyphMetrics() override { return true; };
  virtual std::vector<text::GlyphMetrics> getGlyphMetrics(std::shared_ptr<text::Text> text, const std::vector<text::TextSpan>& spans) override;

  static std::string toPlatformFontFamily(const std::string& family, const std::string& style, int weight);
  static QFont::Weight toPlatformFontWeight(int weight);
  static QFont::Style toPlatformFontStyle(const std::string& style);

private:
  float px2mm(float px, float dotsPerInch);
  float mm2px(float mmm, float dotsPerInch);

  std::unordered_map<std::string, text::GlyphMetrics>& getFontCache(const QFont& font);
  const text::GlyphMetrics& getGlyphMetrics(std::unordered_map<std::string, text::GlyphMetrics>& fontCache, const QFont& font, const std::string& glyph, float dpiX, float dpiY);

  std::unordered_map<FontKey, std::unordered_map<std::string, text::GlyphMetrics>> cache;
};

} // end of: namespace uireferenceimplementation
} // end of: namespace iink
} // end of: namespace myscript

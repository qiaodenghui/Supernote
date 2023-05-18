/*
 * Author : Asa
 * Time : 2019.7.19
*/

#ifndef SNDATALOAD_H
#define SNDATALOAD_H

#include <string>
#include "config.h"
#include "note_global.h"

class NOTE_EXPORT SnDataLoad {

public:

    SnDataLoad();

    unsigned char *  loadImageData( string sNotePath,  int iPage, string sLayerName);
    SNFILE_RETURN_CODE fetchNoteDataFromFileByLayer( string sNotePath,  int iPage,  string sLayerName, ratta_cache_type *arrayDataCache);
    SNFILE_RETURN_CODE fetchNotePathFromFile( std::vector<TrailContainer> &trailsContainer, std::string sNotePath, int iPage);
};
#endif // SNDATALOAD_H

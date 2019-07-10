#ifndef SMAIN_H
#define SMAIN_H
#include "dl_dxf.h"
#include "dl_creationadapter.h"
#include "test_creationclass.h"
class msamin{
public:
    void usage();
    void testReading(char* file);
    void testWriting();
    int smain();
   QList<DL_LineData>sline_data;
};
#endif // SMAIN_H

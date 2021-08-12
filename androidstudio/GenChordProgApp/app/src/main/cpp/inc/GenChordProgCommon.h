//
//  GenChordProgCommon.h
//  GenChordProg
//
//  Created by 佐藤優成 on 2021/08/08.
//

#ifndef GenChordProgCommon_h
#define GenChordProgCommon_h

#include <stdio.h>


#define CHORD_CNT_MAX 16
#define CHORD_SIZE_MAX 30
#define CHORD_PROG_SIZE ( CHORD_CHANGE_CNT_MAX * ( CHORD_SIZE_MAX + 1) )
#define TEMPO_SIZE_MAX 3


void c_GenChordProg(char * p_ptrChordProg, unsigned char p_key_idx, unsigned char p_chordChange_cnt);
void c_GenTempo(char * p_ptrTempo);

#endif /* GenChordProgCommon_h */

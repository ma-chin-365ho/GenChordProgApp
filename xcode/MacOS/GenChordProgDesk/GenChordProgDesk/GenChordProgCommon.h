//
//  GenChordProgCommon.h
//  GenChordProgDesk
//
//  Created by 佐藤優成 on R 6/02/24.
//

#ifndef GenChordProgCommon_h
#define GenChordProgCommon_h

#include <stdio.h>

#define CHORD_CNT_MAX 16
#define CHORD_SIZE_MAX 30
#define CHORD_PROG_SIZE ( CHORD_CNT_MAX * ( CHORD_SIZE_MAX + 1) )
#define TEMPO_SIZE_MAX 3


int c_GetChordProgSize(void);
void c_GenChordProg(char * p_ptrChordProg, unsigned char p_key_idx, unsigned char p_chordChange_cnt);
int c_GetTempoSize(void);
void c_GenTempo(char * p_ptrTempo);
int c_GetNoteNameSize(void);
int c_GetNoteNameIdxMax(void);
void c_GetNoteName(char * p_ptrNoteName, int p_idx);
int c_GetChordChangeCntIdxMax(void);
int c_GetChordChangeCnt(int idx);

#endif /* GenChordProgCommon_h */

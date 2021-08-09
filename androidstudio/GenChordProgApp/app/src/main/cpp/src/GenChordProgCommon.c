//
//  GenChordProgCommon.c
//  GenChordProg
//
//  Created by 佐藤優成 on 2021/08/08.
//

#include "GenChordProgCommon.h"

#include <stdlib.h>
#include <time.h>
#include <string.h>


#define DEBUG_MODE_ON 1
#define DEBUG_MODE_OFF 0
#define DEBUG_MODE DEBUG_MODE_OFF

#define TEXT_SEPARATOR " | "

typedef enum NOTE_NAME_RING_IDX {
    NOTE_NAME_RING_A = 0,
    NOTE_NAME_RING_AB,
    NOTE_NAME_RING_B,
    NOTE_NAME_RING_C,
    NOTE_NAME_RING_CD,
    NOTE_NAME_RING_D,
    NOTE_NAME_RING_DE,
    NOTE_NAME_RING_E,
    NOTE_NAME_RING_F,
    NOTE_NAME_RING_FG,
    NOTE_NAME_RING_G,
    NOTE_NAME_RING_GA,
    NOTE_NAME_RING_MAX
} NOTE_NAME_RING_IDX;

typedef enum DIATONIC_CODE_IDX {
    DIATONIC_CODE_1 = 0,
    DIATONIC_CODE_2,
    DIATONIC_CODE_3,
    DIATONIC_CODE_4,
    DIATONIC_CODE_5,
    DIATONIC_CODE_6,
    DIATONIC_CODE_7,
    DIATONIC_CODE_MAX,
} DIATONIC_CODE_IDX;

typedef enum CHORD_MAJ_MIN_IDX {
    CHORD_MAJ_MIN_MAJOR = 0,
    CHORD_MAJ_MIN_MINOR,
    CHORD_MAJ_MIN_MAX
} CHORD_MAJ_MIN_IDX;

const char noteNameRing[NOTE_NAME_RING_MAX][6+1] =
        {
                "A",
                "A#",
                "B",
                "C",
                "C#",
                "D",
                "D#",
                "E",
                "F",
                "F#",
                "G",
                "G#"
        };

const char nameMajMin[CHORD_MAJ_MIN_MAX][3+1] =
        {
                "",
                "m"
        };

unsigned char diatonicCode_RingIdx[DIATONIC_CODE_MAX];

static void genChord(char chord[CHORD_SIZE_MAX+1]);
static void genDiatonicCode(unsigned char key_idx);


void c_GenChordProg(char * p_ptrChordProg, unsigned char p_key_idx, unsigned char p_chordChange_cnt)
{
    unsigned char key_idx = 3;
    unsigned char chordChange_cnt = 0;
    char chordProg[CHORD_CHANGE_CNT_MAX][CHORD_SIZE_MAX+1] = {0};

    // error handring
    if (!(
            (key_idx < NOTE_NAME_RING_MAX) ||
            (chordChange_cnt < CHORD_CHANGE_CNT_MAX)
    ))
    {
        return;
    }

    // parameter setting
    chordChange_cnt = p_chordChange_cnt;

    // randam
    srand((unsigned int)time(NULL));
    int dummy_rand = rand(); // なぜか1回目は%7すると毎回3になるので一回空振りさせておく。
    int dummy2_rand = rand(); // 時間が近いと連続して同じものになったので、もう一回空振り。

    // printf("time:%d", (unsigned int)time(NULL));

    genDiatonicCode(key_idx);

    for (unsigned char chg_idx = 0; chg_idx < chordChange_cnt; chg_idx++)
    {
        genChord(chordProg[chg_idx]);
        strcat(
                p_ptrChordProg,
                chordProg[chg_idx]
        );

        // Separateor
        if (!(
                (chg_idx == (chordChange_cnt - 1))
        ))
        {
            strcat(
                    p_ptrChordProg,
                    TEXT_SEPARATOR
            );
        }
    }

#if (DEBUG_MODE == DEBUG_MODE_ON)
    for (unsigned char dbg_i = 0; dbg_i < CHORD_CHANGE_CNT_MAX; dbg_i++)
    {
        printf("%s | ", chordProg[dbg_i]);
    }
#endif
}

static void genChord(char chord[CHORD_SIZE_MAX+1])
{
    DIATONIC_CODE_IDX diatonicCode_idx = 0;
    CHORD_MAJ_MIN_IDX chord_maj_min = 0;

    int tmp_rand = rand();
    diatonicCode_idx = tmp_rand % DIATONIC_CODE_MAX;

    // printf("%d ", tmp_rand);
    // printf("%d¥n", diatonicCode_idx);

    switch(diatonicCode_idx){
        case DIATONIC_CODE_1:
            chord_maj_min = CHORD_MAJ_MIN_MAJOR;
            break;
        case DIATONIC_CODE_2:
            chord_maj_min = CHORD_MAJ_MIN_MINOR;
            break;
        case DIATONIC_CODE_3:
            chord_maj_min = CHORD_MAJ_MIN_MINOR;
            break;
        case DIATONIC_CODE_4:
            chord_maj_min = CHORD_MAJ_MIN_MAJOR;
            break;
        case DIATONIC_CODE_5:
            chord_maj_min = CHORD_MAJ_MIN_MAJOR;
            break;
        case DIATONIC_CODE_6:
            chord_maj_min = CHORD_MAJ_MIN_MINOR;
            break;
        case DIATONIC_CODE_7:
            chord_maj_min = CHORD_MAJ_MIN_MINOR;
            break;
        default:
            break;
    }

    memset(chord, 0, CHORD_SIZE_MAX+1);
    sprintf(
            chord,
            "%s%s",
            noteNameRing[diatonicCode_RingIdx[diatonicCode_idx]],
            nameMajMin[chord_maj_min]
    );

    return;
}

static void genDiatonicCode(unsigned char key_idx)
{
    unsigned char tmp_note_idx = 0;

    tmp_note_idx = key_idx;

    // create diatonic code
    diatonicCode_RingIdx[DIATONIC_CODE_1] = tmp_note_idx;
    tmp_note_idx += 2;
    diatonicCode_RingIdx[DIATONIC_CODE_2] = tmp_note_idx % NOTE_NAME_RING_MAX;
    tmp_note_idx += 2;
    diatonicCode_RingIdx[DIATONIC_CODE_3] = tmp_note_idx % NOTE_NAME_RING_MAX;
    tmp_note_idx += 1;
    diatonicCode_RingIdx[DIATONIC_CODE_4] = tmp_note_idx % NOTE_NAME_RING_MAX;
    tmp_note_idx += 2;
    diatonicCode_RingIdx[DIATONIC_CODE_5] = tmp_note_idx % NOTE_NAME_RING_MAX;
    tmp_note_idx += 2;
    diatonicCode_RingIdx[DIATONIC_CODE_6] = tmp_note_idx % NOTE_NAME_RING_MAX;
    tmp_note_idx += 2;
    diatonicCode_RingIdx[DIATONIC_CODE_7] = tmp_note_idx % NOTE_NAME_RING_MAX;

    return;
}


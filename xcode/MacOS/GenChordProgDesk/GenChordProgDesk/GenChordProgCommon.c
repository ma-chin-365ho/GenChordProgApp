//
//  GenChordProgCommon.c
//  GenChordProgDesk
//
//  Created by 佐藤優成 on R 6/02/24.
//

#include "GenChordProgCommon.h"

#include <stdlib.h>
#include <time.h>
#include <string.h>


#define DEBUG_MODE_ON 1
#define DEBUG_MODE_OFF 0
#define DEBUG_MODE DEBUG_MODE_OFF

#define TEXT_SEPARATOR " | "

#define TEMPO_MIN   60
#define TEMPO_MAX  200

#define CHORD_NOTE_STACK_BUFF_SIZE 4
#define NOTE_NAME_SIZE 6+1

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

typedef enum CHORD_NOTE_STACK_IDX {
    CHORD_NOTE_STACK_NONE = 0,
    CHORD_NOTE_STACK_SUS_FOUR,
    CHORD_NOTE_STACK_SIX,
    CHORD_NOTE_STACK_SIX_NINE,
    CHORD_NOTE_STACK_SEVEN,
    CHORD_NOTE_STACK_MAJ_SEVEN,
    CHORD_NOTE_STACK_SEVEN_SUS_FOUR,
    CHORD_NOTE_STACK_SEVEN_FLAT_FIVE,
    CHORD_NOTE_STACK_SEVEN_NINE,
    CHORD_NOTE_STACK_NINE,
    CHORD_NOTE_STACK_ADD_NINE,
    CHORD_NOTE_STACK_ELEVEN,
    CHORD_NOTE_STACK_THIRTEEN,
    CHORD_NOTE_STACK_DIM,
    CHORD_NOTE_STACK_DIM_SEVEN,
    CHORD_NOTE_STACK_AUG,
    CHORD_NOTE_STACK_AUG_SEVEN,
    CHORD_NOTE_STACK_MAX
} CHORD_NOTE_STACK_IDX;

typedef enum CHORD_CHANGE_CNT_IDX {
    CHORD_CHANGE_CNT_IDX_NO_CHANGE = 0,
    CHORD_CHANGE_CNT_IDX_1_TIME,
    CHORD_CHANGE_CNT_IDX_3_TIMES,
    CHORD_CHANGE_CNT_IDX_5_TIMES,
    CHORD_CHANGE_CNT_IDX_7_TIMES,
    CHORD_CHANGE_CNT_IDX_9_TIMES,
    CHORD_CHANGE_CNT_IDX_11_TIMES,
    CHORD_CHANGE_CNT_IDX_13_TIMES,
    CHORD_CHANGE_CNT_IDX_15_TIMES,
    CHORD_CHANGE_CNT_IDX_MAX
} CHORD_CHANGE_CNT_IDX;

struct stDiatonicCode {
    char noteNameRing_idx;
    const CHORD_MAJ_MIN_IDX chord_maj_min;
    const CHORD_NOTE_STACK_IDX chord_note_stack[CHORD_NOTE_STACK_BUFF_SIZE];
    char chord_note_stack_cnt;
} stDiatonicCode;

const char noteNameRing[NOTE_NAME_RING_MAX][NOTE_NAME_SIZE] =
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

const char nameChordNoteStack[CHORD_NOTE_STACK_MAX][24+1] =
    {
        "",
        "sus4",
        "6",
        "6(9)",
        "7",
        "maj7",
        "7sus4",
        "7(-5)",
        "7(9)",
        "9",
        "add9",
        "11",
        "13",
        "dim",
        "dim7",
        "aug",
        "aug7"
    };

const unsigned char chordChangeCnt[CHORD_CHANGE_CNT_IDX_MAX] =
    {
        0,
        1,
        3,
        5,
        7,
        9,
        11,
        13,
        15
    };

struct stDiatonicCode stDiatonicCode_IdxAry[DIATONIC_CODE_MAX] = {
        {0, CHORD_MAJ_MIN_MAJOR,
            {
            CHORD_NOTE_STACK_NONE,
            CHORD_NOTE_STACK_MAJ_SEVEN,
            CHORD_NOTE_STACK_MAX,
            CHORD_NOTE_STACK_MAX
            }, 2
        },
        {1, CHORD_MAJ_MIN_MINOR,
            {
            CHORD_NOTE_STACK_NONE,
            CHORD_NOTE_STACK_SEVEN,
            CHORD_NOTE_STACK_MAX,
            CHORD_NOTE_STACK_MAX
            },2
        },
        {2, CHORD_MAJ_MIN_MINOR,
            {
            CHORD_NOTE_STACK_NONE,
            CHORD_NOTE_STACK_SEVEN,
            CHORD_NOTE_STACK_MAX,
            CHORD_NOTE_STACK_MAX
            },2
        },
        {3, CHORD_MAJ_MIN_MAJOR,
            {
            CHORD_NOTE_STACK_NONE,
            CHORD_NOTE_STACK_MAJ_SEVEN,
            CHORD_NOTE_STACK_MAX,
            CHORD_NOTE_STACK_MAX
            },2
        },
        {4, CHORD_MAJ_MIN_MAJOR,
            {
                CHORD_NOTE_STACK_NONE,
                CHORD_NOTE_STACK_SEVEN,
                CHORD_NOTE_STACK_MAX,
                CHORD_NOTE_STACK_MAX
            },2
        },
        {5, CHORD_MAJ_MIN_MINOR,
            {
                CHORD_NOTE_STACK_NONE,
                CHORD_NOTE_STACK_SEVEN,
                CHORD_NOTE_STACK_MAX,
                CHORD_NOTE_STACK_MAX
            },2
        },
        {6, CHORD_MAJ_MIN_MINOR,
            {
                CHORD_NOTE_STACK_SEVEN_FLAT_FIVE,
                CHORD_NOTE_STACK_MAX,
                CHORD_NOTE_STACK_MAX,
                CHORD_NOTE_STACK_MAX
            }, 1
        }
};

static void genChord(char chord[CHORD_SIZE_MAX+1]);
static void genDiatonicCode(unsigned char key_idx);
static void genTempo(char tempo[TEMPO_SIZE_MAX+1]);
static int rand_range(int range_min,int range_max);


void c_GenChordProg(char * p_ptrChordProg, unsigned char p_key_idx, unsigned char p_chordChange_cnt_idx)
{
    unsigned char key_idx = 3;
    unsigned char chord_cnt = 0;
    char chordProg[CHORD_CNT_MAX][CHORD_SIZE_MAX+1] = {0};

    // error handring
    if (!(
        (p_key_idx < NOTE_NAME_RING_MAX) ||
        (p_chordChange_cnt_idx < CHORD_CHANGE_CNT_IDX_MAX)
    ))
    {
        return;
    }

    if (!(
        (chordChangeCnt[p_chordChange_cnt_idx] <= ( CHORD_CNT_MAX - 1 ))
    ))
    {
        return;
    }

    // parameter setting
    key_idx = p_key_idx;
    chord_cnt = chordChangeCnt[p_chordChange_cnt_idx] + 1;

    // randam
    srand((unsigned int)time(NULL));
    int dummy_rand = rand(); // なぜか1回目は%7すると毎回3になるので一回空振りさせておく。
    int dummy2_rand = rand(); // 時間が近いと連続して同じものになったので、もう一回空振り。

    // printf("time:%d", (unsigned int)time(NULL));

    genDiatonicCode(key_idx);

    for (unsigned char chg_idx = 0; chg_idx < chord_cnt; chg_idx++)
    {
        genChord(chordProg[chg_idx]);
        strcat(
                p_ptrChordProg,
                chordProg[chg_idx]
        );

        // Separateor
        if (!(
                (chg_idx == (chord_cnt - 1))
        ))
        {
            strcat(
                p_ptrChordProg,
                TEXT_SEPARATOR
            );
        }
    }

#if (DEBUG_MODE == DEBUG_MODE_ON)
    for (unsigned char dbg_i = 0; dbg_i < CHORD_CNT_MAX; dbg_i++)
    {
        printf("%s | ", chordProg[dbg_i]);
    }
#endif

    return;
}

int c_GetTempoSize(void)
{
    return TEMPO_SIZE_MAX+1;
}

void c_GenTempo(char * p_ptrTempo)
{
    genTempo(p_ptrTempo);

    return;
}

int c_GetChordProgSize(void)
{
    return CHORD_PROG_SIZE;
}

int c_GetNoteNameSize(void)
{
    return NOTE_NAME_SIZE;
}

int c_GetNoteNameIdxMax(void)
{
    return NOTE_NAME_RING_MAX-1;
}

void c_GetNoteName(char * p_ptrNoteName, int p_idx)
{
    memset(p_ptrNoteName, 0, NOTE_NAME_SIZE);
    if (p_idx < NOTE_NAME_RING_MAX)
    {
        sprintf(
            p_ptrNoteName,
            "%s",
            noteNameRing[p_idx]
        );
    }
    return;
}

int c_GetChordChangeCntIdxMax(void)
{
    return CHORD_CHANGE_CNT_IDX_MAX-1;
}

int c_GetChordChangeCnt(int idx)
{
    if (idx < CHORD_CHANGE_CNT_IDX_MAX) {
        return chordChangeCnt[idx];
    }
    else
    {
        return 0;
    }
}


static void genChord(char chord[CHORD_SIZE_MAX+1])
{
    DIATONIC_CODE_IDX diatonicCode_idx = 0;
    CHORD_MAJ_MIN_IDX chord_maj_min_idx = 0;
    CHORD_NOTE_STACK_IDX chord_note_stack_idx = 0;

    int tmp_rand = rand();
    diatonicCode_idx = tmp_rand % DIATONIC_CODE_MAX;

    chord_maj_min_idx = stDiatonicCode_IdxAry[diatonicCode_idx].chord_maj_min;
    chord_note_stack_idx = stDiatonicCode_IdxAry[diatonicCode_idx].chord_note_stack[(tmp_rand % stDiatonicCode_IdxAry[diatonicCode_idx].chord_note_stack_cnt)];

    memset(chord, 0, CHORD_SIZE_MAX+1);
    sprintf(
            chord,
            "%s%s%s",
            noteNameRing[stDiatonicCode_IdxAry[diatonicCode_idx].noteNameRing_idx],
            nameMajMin[chord_maj_min_idx],
            nameChordNoteStack[chord_note_stack_idx]
    );

    return;
}

static void genDiatonicCode(unsigned char key_idx)
{
    unsigned char tmp_note_idx = 0;

    tmp_note_idx = key_idx;

    // create diatonic code
    stDiatonicCode_IdxAry[DIATONIC_CODE_1].noteNameRing_idx = tmp_note_idx;
    tmp_note_idx += 2;
    stDiatonicCode_IdxAry[DIATONIC_CODE_2].noteNameRing_idx = tmp_note_idx % NOTE_NAME_RING_MAX;
    tmp_note_idx += 2;
    stDiatonicCode_IdxAry[DIATONIC_CODE_3].noteNameRing_idx = tmp_note_idx % NOTE_NAME_RING_MAX;
    tmp_note_idx += 1;
    stDiatonicCode_IdxAry[DIATONIC_CODE_4].noteNameRing_idx = tmp_note_idx % NOTE_NAME_RING_MAX;
    tmp_note_idx += 2;
    stDiatonicCode_IdxAry[DIATONIC_CODE_5].noteNameRing_idx = tmp_note_idx % NOTE_NAME_RING_MAX;
    tmp_note_idx += 2;
    stDiatonicCode_IdxAry[DIATONIC_CODE_6].noteNameRing_idx = tmp_note_idx % NOTE_NAME_RING_MAX;
    tmp_note_idx += 2;
    stDiatonicCode_IdxAry[DIATONIC_CODE_7].noteNameRing_idx = tmp_note_idx % NOTE_NAME_RING_MAX;

    return;
}

static void genTempo(char tempo[TEMPO_SIZE_MAX+1])
{
    srand((unsigned int)time(NULL));
    int dummy_rand = rand(); /* NOTE: [iOS版] なぜかこれが無いと毎回同じ値になるので一回空振りさせておく。 */
    int dummy2_rand = rand(); /* NOTE: [iOS版] 時間が近いと連続して同じものになったので、もう一回空振り。 */

    int rand_tempo = rand_range(TEMPO_MIN, TEMPO_MAX);

    memset(tempo, 0, TEMPO_SIZE_MAX+1);
    sprintf(
            tempo,
            "%3d",
            rand_tempo
    );

    return;
}

static int rand_range(int range_min,int range_max)
{
    return range_min + (int)(rand()*(range_max-range_min+1.0)/(1.0+RAND_MAX));
}


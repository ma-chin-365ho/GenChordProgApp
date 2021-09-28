var factory = require('./GenChordProgCommon.js');

var i_chord_prog_size = 512; /* CHORD_PROG_SIZE */
var i_tempo_size = 4; /* CHORD_PROG_SIZE */

async function genChordProgJson(key_idx, hordChange_cnt_idx)
{
  var s_ChordProg = "";
  var s_Tempo = "";
  var p_key_idx = key_idx;
  var p_chordChange_cnt_idx = hordChange_cnt_idx;

  // instance = Module
  await factory().then(async function (instance) {

    var p_ptrChordProg = instance._malloc(i_chord_prog_size); 
    var p_ptrTempo = instance._malloc(i_tempo_size); 
    var InitValArray_ChordProg = [...Array(i_chord_prog_size)].map(() => 0);
    var InitValArray_Tempo = [...Array(i_tempo_size)].map(() => 0);
  
    // Initialize
    instance.HEAP8.set(InitValArray_ChordProg, p_ptrChordProg);
    instance.HEAP8.set(InitValArray_Tempo, p_ptrTempo);

    instance.ccall(
      "c_GenChordProg",
      null,
      ["number", "number", "number"],
      [p_ptrChordProg, p_key_idx, p_chordChange_cnt_idx]
    );

    instance.ccall(
      "c_GenTempo",
      null,
      ["number"],
      [p_ptrTempo]
    );

    s_ChordProg = instance.UTF8ToString(p_ptrChordProg);
    s_Tempo =  instance.UTF8ToString(p_ptrTempo);

    instance._free(p_ptrChordProg);
    instance._free(p_ptrTempo);
  });

  // console.log(s_ChordProg);
  // console.log(s_Tempo);

  return {chordProg : s_ChordProg, tempo : s_Tempo};
}

module.exports.gen = genChordProgJson;

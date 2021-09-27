var factory = require('./GenChordProgCommon.js');

var i_chord_prog_size = 512; /* CHORD_PROG_SIZE */

// instance = Module
factory().then((instance) => {

  var p_key_idx = 3;
  var p_chordChange_cnt_idx = 4;
  var p_ptrChordProg = instance._malloc(i_chord_prog_size); 
  var InitValArray = [...Array(i_chord_prog_size)].map(() => 0);
  
  instance.HEAP8.set(InitValArray, p_ptrChordProg);

  instance.ccall(
    "c_GenChordProg",
    null,
    ["number", "number", "number"],
    [p_ptrChordProg, p_key_idx, p_chordChange_cnt_idx]
  );

  // console.log(String.fromCodePoint(instance.getValue(p_ptrChordProg, "i8")));
  console.log(instance.UTF8ToString(p_ptrChordProg));

  instance._free(p_ptrChordProg);
});

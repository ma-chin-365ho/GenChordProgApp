
const cpg = require('./WrapGenChordProgCommon.js');

async function main() {
    var json = await cpg.gen(3,5);
    console.log(json);
}
  
  main();

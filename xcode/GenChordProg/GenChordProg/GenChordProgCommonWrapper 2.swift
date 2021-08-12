//
//  GenChordProgCommonWrapper.swift
//  GenChordProg
//
//  Created by 佐藤優成 on 2021/08/08.
//

import Foundation

class GenChordProgCommonWrapper
{
    func genChordProg(p_key_idx: Int , p_chordChange_cnt: Int ) -> String
    {
        // let chordProgSize = Int(CHORD_PROG_SIZE)
        let chordProgSize = 16*(40+1)
        let ptrChordProg : UnsafeMutablePointer<CChar> = UnsafeMutablePointer<CChar>.allocate(capacity: chordProgSize)
        var strGenChordProg : String? = ""
        
        c_GenChordProg(ptrChordProg, 0, 4)
        strGenChordProg = String(cString: ptrChordProg, encoding: .utf8)
        // print(ptrChordProg)
        ptrChordProg.deallocate()
        
        if let r_genChordProg = strGenChordProg
        {
            return r_genChordProg
        }
        else
        {
            return ""
        }
    }
}

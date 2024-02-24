//
//  GenChordProgCommonWrapper.swift
//  GenChordProg
//
//  Created by 佐藤優成 on 2021/08/08.
//

import Foundation

class GenChordProgCommonWrapper
{
    func getChordProgSize() -> Int
    {
        return Int(c_GetChordProgSize())
    }
    
    func genChordProg(p_key_idx: Int , p_chordChange_cnt: Int ) -> String
    {
        let chordProgSize = self.getChordProgSize()
        let ptrChordProg : UnsafeMutablePointer<CChar> = UnsafeMutablePointer<CChar>.allocate(capacity: chordProgSize)
        var strGenChordProg : String? = ""
        
        c_GenChordProg(ptrChordProg, UInt8(p_key_idx), UInt8(p_chordChange_cnt))
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
    
    func getTempoSize() -> Int
    {
        return Int(c_GetTempoSize())
    }
    
    func genTempo() -> String
    {
        let tempoSize = self.getTempoSize()
        let ptrTempo : UnsafeMutablePointer<CChar> = UnsafeMutablePointer<CChar>.allocate(capacity: tempoSize)
        var strTempo : String? = ""
        
        c_GenTempo(ptrTempo)
        strTempo = String(cString: ptrTempo, encoding: .utf8)
        ptrTempo.deallocate()
        
        if let r_genTempo = strTempo
        {
            return r_genTempo
        }
        else
        {
            return ""
        }
    }

    func getNoteNameSize() -> Int
    {
        return Int(c_GetNoteNameSize())
    }

    func getNoteNameIdxMax() -> Int
    {
        return Int(c_GetNoteNameIdxMax())
    }
    
    func getNoteName(p_key_idx : Int) -> String
    {
        let noteNameSize = self.getNoteNameSize()
        let ptrNoteName : UnsafeMutablePointer<CChar> = UnsafeMutablePointer<CChar>.allocate(capacity: noteNameSize)
        var strNoteName : String? = ""
        
        c_GetNoteName(ptrNoteName, Int32(p_key_idx))
        strNoteName = String(cString: ptrNoteName, encoding: .utf8)
        ptrNoteName.deallocate()
        
        if let r_getNoteName = strNoteName
        {
            return r_getNoteName
        }
        else
        {
            return ""
        }
    }
    
    
    func getChordChangeCntIdxMax() -> Int
    {
        return Int(c_GetChordChangeCntIdxMax())
    }
    
    func getChordChangeCnt(p_idx : Int) -> Int
    {
        return Int(c_GetChordChangeCnt(Int32(p_idx)))
    }
    
    /*
    func getNoteNames() -> [String]
    {
        var noteNames : [String] = []
        for idx in 0...self.getNoteNameIdxMax()
        {
            noteNames.append(self.getNoteName(p_key_idx: idx))
        }
        return noteNames
    }
     */
}

//
//  ContentView.swift
//  GenChordProg
//
//  Created by 佐藤優成 on 2021/08/08.
//

import SwiftUI

struct ContentView: View {
    
    @State var stateText_ChordProg :String = ""
    let mGenChordProgCommonWrapper = GenChordProgCommonWrapper()
    
    var body: some View {
        Text(stateText_ChordProg)
            .padding()
            .onAppear {
                self.stateText_ChordProg =
                    self.mGenChordProgCommonWrapper.genChordProg(
                        p_key_idx: 0 ,
                        p_chordChange_cnt: 4
                    )
                /*
                    var vChordProg: String?
                    print("genChordProg Start")
                    vChordProg = self.mGenChordProgCommonWrapper.genChordProg(p_key_idx: 0 , p_chordChange_cnt: 4 )
                    print(vChordProg)
                    print("genChordProg End")
                */
            }
            .onTapGesture {
                self.stateText_ChordProg = self.mGenChordProgCommonWrapper.genChordProg(p_key_idx: 0 , p_chordChange_cnt: 4 )
            }
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
    }
}


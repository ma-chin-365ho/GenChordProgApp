//
//  ContentView.swift
//  GenChordProgDesk
//
//  Created by 佐藤優成 on R 6/02/24.
//

import SwiftUI

struct ContentView: View {
    
    @State private var stateText_ChordProg :String = ""
    @State private var stateText_Tempo : String = ""
    @State private var keyIdx : Int = 3
    @State private var chordChangeCntIdx : Int = 4
    
    let mGenChordProgCommonWrapper = GenChordProgCommonWrapper()
    
    var body: some View {
        ZStack {
            Color.clear
                .ignoresSafeArea()
            VStack {
                List {
                    Text(stateText_ChordProg)
                        .padding()
                        .onAppear {
                            self.updTextChordProg(p_key_idx: keyIdx, p_chordChange_cnt: chordChangeCntIdx)
                        }
                        .onTapGesture {
                            self.updTextChordProg(p_key_idx: keyIdx, p_chordChange_cnt: chordChangeCntIdx)
                        }
                    Picker("Key : ", selection: $keyIdx) {
                        ForEach(0...mGenChordProgCommonWrapper.getNoteNameIdxMax(), id: \.self) { id in
                            Text(mGenChordProgCommonWrapper.getNoteName(p_key_idx: id))
                        }
                    }
                    .onChange(of: keyIdx) { newValue in
                        self.updTextChordProg(p_key_idx: newValue, p_chordChange_cnt: chordChangeCntIdx)
                    }
                    Picker("Change Count : ", selection: $chordChangeCntIdx) {
                        ForEach(0...mGenChordProgCommonWrapper.getChordChangeCntIdxMax(), id: \.self) { id in
                            let changeCnt = mGenChordProgCommonWrapper.getChordChangeCnt(p_idx: id)
                            if (changeCnt == 0) {
                                Text("No Change")
                            } else if (changeCnt == 1) {
                                Text("\(changeCnt) time")
                            } else {
                                Text("\(changeCnt) times")
                            }
                        }
                    }
                    .onChange(of: chordChangeCntIdx) { newValue in
                        self.updTextChordProg(p_key_idx: keyIdx, p_chordChange_cnt: newValue)
                    }
                    HStack {
                        Text("Tempo : ")
                        Spacer()
                        Text(stateText_Tempo)
                            .onAppear {
                                self.updTextTempo()
                            }
                            .onTapGesture {
                                self.updTextTempo()
                            }
                    }
                    HStack {
                        Spacer()
                        Image(systemName: "wand.and.stars.inverse")
                            .onTapGesture {
                                self.updTextChordProg(p_key_idx: keyIdx, p_chordChange_cnt: chordChangeCntIdx)
                                self.updTextTempo()
                            }
                    }
                }
            }
        }
    }
    
    func updTextChordProg (p_key_idx: Int, p_chordChange_cnt : Int) {
        self.stateText_ChordProg =
            self.mGenChordProgCommonWrapper.genChordProg(
                p_key_idx: p_key_idx ,
                p_chordChange_cnt: p_chordChange_cnt
            )
    }
    
    func updTextTempo () {
        self.stateText_Tempo =
            self.mGenChordProgCommonWrapper.genTempo()
    }
}
#Preview {
    ContentView()
}

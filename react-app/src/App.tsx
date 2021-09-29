import React, { useState ,useEffect} from 'react';
import logo from './logo.svg';
import './App.css';

interface CpgIf{
  chordProg:string
  tempo:string
}

function App() {
  const [txtChordProg, setTxtChordProg] = useState({chordProg : "", tempo : ""});

  useEffect(() => {
    console.log('useEffect...');
    fetch('http://localhost:4000/api/v1.0/chordproggen', {method: 'GET'})
      .then(res => res.json())
      .then(data => setTxtChordProg(data));
   },[]);

  return (
    <div className="App">
      <body>
        {
          txtChordProg.chordProg
        }
      </body>
    </div>
  );
}

export default App;

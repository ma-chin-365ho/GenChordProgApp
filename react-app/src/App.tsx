import React, { useState ,useEffect} from 'react';
import {Button, Typography, Select, MenuItem, FormControl} from '@material-ui/core';
import {Stack ,Grid} from '@mui/material';
import logo from './logo.svg';
import './App.css';

function App() {
  const [txtChordProg, setTxtChordProg] = useState({chordProg : "", tempo : ""});
  const [key, setKey] = useState(3);
  const [chgCnt, setChgCnt] = useState(5);

  const fetchCpg = (key :number, chgcnt: number ) => {
    fetch(
      'http://localhost:4000/api/v1.0/chordproggen?key=' + key.toString() + '&chgcnt=' + chgcnt.toString(), 
      {method: 'GET'}
    )
    .then(res => res.json())
    .then(data => setTxtChordProg(data));
  }

  const handleOnClickUpdate = () => {
    fetchCpg(key, chgCnt);
  }

  useEffect(() => {
    // console.log('useEffect...');
    fetchCpg(key, chgCnt);
  },[]);

  const handleOnChangeKey = (e: any) => {
    let sltKey : number = e.target.value;
    setKey(sltKey);
    fetchCpg(sltKey, chgCnt);
  }
  const handleOnChangeChgCnt = (e : any) => {
    let sltChgCnt : number = e.target.value;
    setChgCnt(sltChgCnt);
    fetchCpg(key, sltChgCnt);
  }

  return (
    <div className="App">
      <Stack spacing={3}>
        <Typography variant="h4">
          {" "}
        </Typography>
        <Grid container spacing={2}>
          <Grid xs={3}>
          </Grid>
          <Grid xs={6}>
            <Typography variant="h3">
              {txtChordProg.chordProg}
            </Typography>
          </Grid>
          <Grid xs={3}>
          </Grid>
        </Grid>
        <Typography variant="h4">
          {"♩ = " + txtChordProg.tempo}
        </Typography>
        <Grid container spacing={2}>
          <Grid xs={4}>
            <FormControl>
              <Typography>Key</Typography>
              <Select
                value={key}
                label="Key"
                onChange={handleOnChangeKey}
              >
                <MenuItem value={0}>A</MenuItem>
                <MenuItem value={1}>A#/Bb</MenuItem>
                <MenuItem value={2}>B</MenuItem>
                <MenuItem value={3}>C</MenuItem>
                <MenuItem value={4}>C#/Db</MenuItem>
                <MenuItem value={5}>D</MenuItem>
                <MenuItem value={6}>D#/Eb</MenuItem>
                <MenuItem value={7}>E</MenuItem>
                <MenuItem value={8}>F</MenuItem>
                <MenuItem value={9}>F#/Gb</MenuItem>
                <MenuItem value={10}>G</MenuItem>
                <MenuItem value={11}>G#/Ab</MenuItem>
              </Select>
            </FormControl>
          </Grid>
          <Grid xs={4}>
            <FormControl>
              <Typography>Chord Change Count</Typography>
              <Select
                value={chgCnt}
                label="Chord Change Count"
                onChange={handleOnChangeChgCnt}
              >
                <MenuItem value={0}>No Change</MenuItem>
                <MenuItem value={1}>1 Time</MenuItem>
                <MenuItem value={2}>3 Times</MenuItem>
                <MenuItem value={3}>5 Times</MenuItem>
                <MenuItem value={4}>7 Times</MenuItem>
                <MenuItem value={5}>9 Times</MenuItem>
                <MenuItem value={6}>11 Times</MenuItem>
                <MenuItem value={7}>13 Times</MenuItem>
                <MenuItem value={8}>15 Times</MenuItem>
              </Select>
            </FormControl>
          </Grid>
          <Grid xs={4}>
            <Button variant="contained" color="primary" onClick={handleOnClickUpdate}>
              UPDATE
            </Button>
          </Grid>
        </Grid>
      </Stack>
    </div>
  );
}

export default App;

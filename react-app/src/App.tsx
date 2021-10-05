import React, { useState ,useEffect} from 'react';
import {Button, Typography, Box} from '@material-ui/core';
import {Stack ,Grid} from '@mui/material';
import logo from './logo.svg';
import './App.css';

interface CpgIf{
  chordProg:string
  tempo:string
}

function App() {
  const [txtChordProg, setTxtChordProg] = useState({chordProg : "", tempo : ""});

  const fetchCpg = () => {
    fetch('http://localhost:4000/api/v1.0/chordproggen', {method: 'GET'})
      .then(res => res.json())
      .then(data => setTxtChordProg(data));
  }

  const handleOnClickUpdate = () => {
    fetchCpg();
  }

  useEffect(() => {
    console.log('useEffect...');
    fetchCpg();
  },[]);

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
          </Grid>
          <Grid xs={4}>
            <Button variant="contained" color="primary" onClick={handleOnClickUpdate}>
              UPDATE
            </Button>
          </Grid>
          <Grid xs={4}>
          </Grid>
        </Grid>
      </Stack>
    </div>
  );
}

export default App;

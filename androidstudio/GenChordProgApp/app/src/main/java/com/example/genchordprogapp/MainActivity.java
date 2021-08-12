package com.example.genchordprogapp;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;

import android.view.View;
import android.widget.TextView;
import android.widget.Spinner;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemSelectedListener;


import com.example.genchordprogapp.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'genchordprogapp' library on application startup.
    static {
        System.loadLibrary("genchordprogapp");
    }

    private ActivityMainBinding binding;
    private int mKeyIdx = 3;
    private int mChangeCountIdx = 4;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        // Chord Prog Text
        TextView tv = binding.chordprogText;
        tv.setText(genChordProgFromJNI(mKeyIdx, mChangeCountIdx));
        tv.setOnClickListener( v -> {
            binding.chordprogText.setText(genChordProgFromJNI(mKeyIdx, mChangeCountIdx));
        });

        // Tempo Text
        TextView tv_tv = binding.textViewTempoValue;
        tv_tv.setText(genTempoFromJNI());
        tv_tv.setOnClickListener( v -> {
            binding.textViewTempoValue.setText(genTempoFromJNI());
        });

        // Key SelectBox
        Spinner spinnerKey = (Spinner) findViewById(R.id.spinnerKey);
        // Create an ArrayAdapter using the string array and a default spinner layout
        ArrayAdapter<CharSequence> adapterKey = ArrayAdapter.createFromResource(this,
                R.array.keys_array, android.R.layout.simple_spinner_item);
        // Specify the layout to use when the list of choices appears
        adapterKey.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        // Apply the adapter to the spinner
        spinnerKey.setAdapter(adapterKey);
        spinnerKey.setOnItemSelectedListener(new OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> parent,
                                       View view, int position, long id) {
                Spinner spinner = (Spinner)parent;
                mKeyIdx = spinner.getSelectedItemPosition();
                binding.chordprogText.setText(genChordProgFromJNI(mKeyIdx, mChangeCountIdx));
            }
            public void onNothingSelected(AdapterView<?> parent) {
            }
        });
        spinnerKey.setSelection(mKeyIdx);

        // ChangeCounts SelectBox
        Spinner spinnerChangeCount = (Spinner) findViewById(R.id.spinnerChangeCount);
        // Create an ArrayAdapter using the string array and a default spinner layout
        ArrayAdapter<CharSequence> adapterChangeCount = ArrayAdapter.createFromResource(this,
                R.array.change_counts_array, android.R.layout.simple_spinner_item);
        // Specify the layout to use when the list of choices appears
        adapterKey.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        // Apply the adapter to the spinner
        spinnerChangeCount.setAdapter(adapterChangeCount);
        spinnerChangeCount.setOnItemSelectedListener(new OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> parent,
                                       View view, int position, long id) {
                Spinner spinner = (Spinner)parent;
                mChangeCountIdx = spinner.getSelectedItemPosition();
                binding.chordprogText.setText(genChordProgFromJNI(mKeyIdx, mChangeCountIdx));
            }
            public void onNothingSelected(AdapterView<?> parent) {
            }
        });
        spinnerChangeCount.setSelection(mChangeCountIdx);

        // Reload Button
        Button button = (Button) findViewById(R.id.buttonReload);
        button.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                // Do something in response to button click
                binding.chordprogText.setText(genChordProgFromJNI(mKeyIdx, mChangeCountIdx));
                binding.textViewTempoValue.setText(genTempoFromJNI());
            }
        });
    }

    /**
     * A native method that is implemented by the 'genchordprogapp' native library,
     * which is packaged with this application.
     */
    public native String genChordProgFromJNI(int p_key_idx, int p_chordChange_cnt);
    public native String genTempoFromJNI();
}
package com.example.genchordprogapp;

import androidx.appcompat.app.AppCompatActivity;

import android.media.Image;
import android.os.Bundle;

import android.view.View;
import android.widget.TextView;
import android.widget.Spinner;
import android.widget.ArrayAdapter;
import android.widget.ImageButton;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemSelectedListener;


import com.example.genchordprogapp.databinding.ActivityMainBinding;

// Mobile Ads SDK
import com.google.android.gms.ads.MobileAds;
import com.google.android.gms.ads.initialization.InitializationStatus;
import com.google.android.gms.ads.initialization.OnInitializationCompleteListener;
import com.google.android.gms.ads.AdRequest;
import com.google.android.gms.ads.AdView;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'genchordprogapp' library on application startup.
    static {
        System.loadLibrary("genchordprogapp");
    }

    private ActivityMainBinding binding;
    private int mKeyIdx = 3;
    private int mChangeCountIdx = 4;

    private AdView mAdView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        // Mobile Ads SDK
        MobileAds.initialize(this, new OnInitializationCompleteListener() {
            @Override
            public void onInitializationComplete(InitializationStatus initializationStatus) {
            }
        });
        mAdView = findViewById(R.id.adView);
        AdRequest adRequest = new AdRequest.Builder().build();
        mAdView.loadAd(adRequest);

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
                R.array.keys_array, R.layout.custom_spinner);
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
                R.array.change_counts_array, R.layout.custom_spinner);
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
        ImageButton imgbtn = (ImageButton) findViewById(R.id.imageButtonReload);
        imgbtn.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                // Do something in response to button click
                binding.chordprogText.setText(genChordProgFromJNI(mKeyIdx, mChangeCountIdx));
                binding.textViewTempoValue.setText(genTempoFromJNI());
            }
        });
    }

    /** Called when leaving the activity */
    @Override
    public void onPause() {
        if (mAdView != null) {
            mAdView.pause();
        }
        super.onPause();
    }

    /** Called when returning to the activity */
    @Override
    public void onResume() {
        super.onResume();
        if (mAdView != null) {
            mAdView.resume();
        }
    }

    /** Called before the activity is destroyed */
    @Override
    public void onDestroy() {
        if (mAdView != null) {
            mAdView.destroy();
        }
        super.onDestroy();
    }

    /**
     * A native method that is implemented by the 'genchordprogapp' native library,
     * which is packaged with this application.
     */
    public native String genChordProgFromJNI(int p_key_idx, int p_chordChange_cnt);
    public native String genTempoFromJNI();
}
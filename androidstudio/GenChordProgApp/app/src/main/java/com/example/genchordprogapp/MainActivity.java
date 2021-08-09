package com.example.genchordprogapp;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.TextView;

import com.example.genchordprogapp.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'genchordprogapp' library on application startup.
    static {
        System.loadLibrary("genchordprogapp");
    }

    private ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        // Example of a call to a native method
        TextView tv = binding.chordprogText;
        tv.setText(genChordProgFromJNI());
        tv.setOnClickListener( v -> {
            binding.chordprogText.setText(genChordProgFromJNI());
        });
    }

    /**
     * A native method that is implemented by the 'genchordprogapp' native library,
     * which is packaged with this application.
     */
    public native String genChordProgFromJNI();
}
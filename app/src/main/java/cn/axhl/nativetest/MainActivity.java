package cn.axhl.nativetest;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.os.Looper;
import android.widget.Toast;

import cn.axhl.util.NativeLib;

public class MainActivity extends AppCompatActivity {
    static {
        System.loadLibrary("NativeCode");
    }
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        new Thread(new Runnable() {

            @Override
            public void run() {
                Looper.prepare();
                String str = NativeLib.GetNativeString();
                Toast.makeText(getApplicationContext(), str, Toast.LENGTH_LONG);
            }
        }).start();
    }
}
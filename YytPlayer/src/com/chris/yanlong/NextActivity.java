
package com.chris.yanlong;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;

public class NextActivity extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        Log.v("NextActivity", "onCreate");
        setContentView(R.layout.activity_next);  //
        
        findViewById(R.id.rl_viewObj).setOnClickListener(new View.OnClickListener() {

            @Override
            public void onClick(View v) {
                Intent intent = new Intent(NextActivity.this, MainActivity.class);
                startActivity(intent);
            }
            
              
        });
    }
}

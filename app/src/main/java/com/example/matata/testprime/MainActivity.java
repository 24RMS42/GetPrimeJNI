package com.example.matata.testprime;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity implements View.OnClickListener{

    private EditText mTxtResult;
    private EditText mEdtFrom, mEdtTo;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mTxtResult = (EditText) findViewById(R.id.textResult);
        mEdtFrom = (EditText)findViewById(R.id.edtFrom);
        mEdtTo = (EditText)findViewById(R.id.edtTo);
        Button mBtnCal = (Button)findViewById(R.id.btnCalculate);
        mBtnCal.setOnClickListener(this);
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native int[] getPrime(int from, int to);

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.btnCalculate:

                String validate_result = validate(mEdtFrom.getText().toString(), mEdtTo.getText().toString());
                if (!validate_result.equals("")){
                    Toast.makeText(this,validate_result, Toast.LENGTH_LONG).show();
                    return;
                }

                int nFrom = Integer.parseInt(mEdtFrom.getText().toString());
                int nTo   = Integer.parseInt(mEdtTo.getText().toString());
                int[] prime_result_array = getPrime(nFrom, nTo);

                String prime_result_str = "";
                if (prime_result_array != null && prime_result_array.length > 0)
                {
                    for (int i = 0; i < prime_result_array.length; i++)
                    {
                        prime_result_str += String.valueOf(prime_result_array[i]);
                        prime_result_str += ",";
                    }
                }else
                    prime_result_str = "There is no result";

                mTxtResult.setText(prime_result_str);

                break;

        }
    }

    /**
     * Validate input value
     *
     * @param from
     * @param to
     * @return   error message
     *
     */
    String validate(String from, String to)
    {
        if (from.equals("") || to.equals(""))
            return "Please input number";

        int nFrom = Integer.parseInt(from);
        int nTo   = Integer.parseInt(to);

        if (nFrom > nTo)
            return "Second number can't be greater than First one";

        if (nFrom == 0)
            return "Please input number greater than 0";
        else
            return "";
    }
}

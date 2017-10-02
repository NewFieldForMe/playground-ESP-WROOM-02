package com.newfield1001.yamadaryo.esp_8266_connection

import android.os.AsyncTask
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.widget.Button
import android.widget.Toast
import android.util.Log
import java.io.BufferedReader
import java.io.BufferedWriter
import java.io.InputStreamReader
import java.io.OutputStreamWriter
import java.net.Socket

open class NetworkAsyncTask : AsyncTask<Void, Void, String>() {

    override fun doInBackground(vararg params: Void): String? {
        return null
    }
}

class ScreenChangeActivity : AppCompatActivity() {
    private val esp8266_IP = "192.168.11.7"    //アクセス先IP
    private val esp8266_Port = 8090 //アクセス先ポート

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_screen_change)

        val nekoButton = findViewById(R.id.neko_button) as Button?
        val inuButton = findViewById(R.id.inu_button) as Button?
        nekoButton?.setOnClickListener{ nekoButtonClick() }
        inuButton?.setOnClickListener{ inuButtonClick() }
    }

    fun nekoButtonClick() {
//        Toast.makeText(this, "Neko", Toast.LENGTH_LONG).show()
        object : NetworkAsyncTask() {
            override fun doInBackground(vararg params: Void): String? {
                return connectTCPServer("Neko!!")
            }
        }.execute()
    }

    fun inuButtonClick() {
//        Toast.makeText(this, "Inu", Toast.LENGTH_LONG).show()
        object : NetworkAsyncTask() {
            override fun doInBackground(vararg params: Void): String? {
                return connectTCPServer("Inu!!")
            }
        }.execute()
    }

    fun connectTCPServer(message: String): String? {
        try {
            //通信用ソケット作成
            val socket = Socket(esp8266_IP, esp8266_Port)

            val inStream = socket.getInputStream()
            val outStream = socket.getOutputStream()

            val br = BufferedReader(InputStreamReader(inStream, "UTF-8"))
            val bw = BufferedWriter(OutputStreamWriter(outStream, "UTF-8"))

            //テキストを送る
            bw.write(message)

            //データを確定させて通信処理を起こさせる
            bw.flush()

            //相手からのデータ待ち
            val szData = br.readLine()

            //表示する
            Log.d("OK!!", "受信文字列:" + szData)

            //後処理
            inStream.close()
            outStream.close()
            socket.close()
        } catch (e: Exception) {
            e.printStackTrace()
        }
        return "message"
    }
}

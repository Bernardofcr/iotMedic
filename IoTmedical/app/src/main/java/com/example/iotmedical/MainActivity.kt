package com.example.iotmedical

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.*
import com.google.firebase.database.DataSnapshot
import com.google.firebase.database.DatabaseError
import com.google.firebase.database.ValueEventListener
import com.google.firebase.database.ktx.database
import com.google.firebase.ktx.Firebase
import android.util.Log

class MainActivity : AppCompatActivity() {
    val database=Firebase.database
    var doorOnline=false
        override fun onCreate(savedInstanceState: Bundle?) {
            super.onCreate(savedInstanceState)
            setContentView(R.layout.activity_main)
            val liberarMedicamento=findViewById<Button>(R.id.liberar_medicamento)
            val dosagem1=findViewById<EditText>(R.id.dosagem1value)
            val dosagem2=findViewById<EditText>(R.id.dosagem2value)
            val pressao=findViewById<TextView>(R.id.pressao_value)
            val ajuda=findViewById<TextView>(R.id.ajuda_text)
            val ajudaBG=findViewById<RelativeLayout>(R.id.ajuda)
            addDoorIsOpenListener()
            //liberarMedicamento.setOnClickListener {
                //database.getReference("medicine").setValue(get)
            //}
        }
        private fun addDoorIsOpenListener() {
                val doorListener = object : ValueEventListener {
                        override fun onDataChange(snapshot: DataSnapshot) {
                                val value = snapshot.value.toString()
                                if (value == "1") {
                                        doorOnline = true
                                } else if (value == "0") {
                                        doorOnline = false
                                }
                        }

                        override fun onCancelled(error: DatabaseError) {
                                Log.w("Firebase", "loadPost: Cancelled", error.toException())
                        }
                }
                database.getReference("door_is_open").addValueEventListener(doorListener)
        }
}
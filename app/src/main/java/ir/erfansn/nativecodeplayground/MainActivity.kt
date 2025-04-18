package ir.erfansn.nativecodeplayground

import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.enableEdgeToEdge
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import ir.erfansn.nativecodeplayground.ui.theme.NativeCodePlaygroundTheme

class MainActivity : ComponentActivity() {

    private val company = Company(listOf("Erfan", "Ali", "Reza"))

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContent {
            NativeCodePlaygroundTheme {
                Scaffold(modifier = Modifier.fillMaxSize()) { innerPadding ->
                    Column(modifier = Modifier.padding(innerPadding)) {
                        Text("With JNI:")
                        Greeting(
                            name = concatenateMembersNameJni(company),
                        )
                        Spacer(modifier = Modifier.height(16.dp))
                        Text("With JNI Bind:")
                        Greeting(
                            name = concatenateMembersNameJniBind(company),
                        )
                    }
                }
            }
        }
    }

    private external fun concatenateMembersNameJni(company: Company): String

    private external fun concatenateMembersNameJniBind(company: Company): String

    companion object {
        init {
            System.loadLibrary("nativecodeplayground")
        }
    }
}

@Composable
fun Greeting(name: String, modifier: Modifier = Modifier) {
    Text(
        text = "Hello $name!",
        modifier = modifier
    )
}

@Preview(showBackground = true)
@Composable
fun GreetingPreview() {
    NativeCodePlaygroundTheme {
        Greeting("Android")
    }
}
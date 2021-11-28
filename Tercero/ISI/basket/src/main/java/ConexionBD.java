import com.google.auth.Credentials;
import com.google.auth.oauth2.AccessToken;
import com.google.auth.oauth2.GoogleCredentials;
import com.google.cloud.firestore.Firestore;
import com.google.cloud.storage.Storage;
import com.google.cloud.storage.StorageOptions;
import com.google.*;
import com.google.firebase.FirebaseOptions;
import com.google.firebase.*;
import com.google.firebase.cloud.*;
import com.google.firebase.FirebaseApp;
import com.google.firebase.FirebaseOptions;



public class ConexionBD {

	
	// Use the application default credentials
	

	
	Credentials credentials = GoogleCredentials.create(new AccessToken(null, null));
	Storage storage = StorageOptions.newBuilder()
	    .setCredentials(credentials)
	    .build()
	    .getService();
}

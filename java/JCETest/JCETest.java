//package com.amlogic.JCETest ;
import javax.crypto.*;
import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.security.*;
import java.security.interfaces.*;
import java.security.spec.*;
import java.util.logging.Logger;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import javax.crypto.Cipher;
import javax.crypto.CipherSpi;
 

public class JCETest{

public static final String stringToEncrypt="This is a test.";

	private static final String PrivateKeyData =
		"MIIEvwIBADANBgkqhkiG9w0BAQEFAASCBKkwggSlAgEAAoIBAQDn10TyouJ4i2wf\n" +
		"VaCOtwVEqPp5RaqL5sYs5fUcvdTcaEL+PRCD3S7ewb/UJS3ALm85i98OYUjqhIVe\n" +
		"LkQtptYmZPZ0ofMEkpreT2iT7y325xGox3oNkcnZgIIuUNEpIq/qQOqfDhTA92k4\n" +
		"xfOIL8AyPdn+VRVfUbtZIcIBYp/XM1LV4u+qv5ugSNe4E6K2dn9sPM8etM5nPQN7\n" +
		"DS6jDF//6wb40Ird5AlXGpxon+8QcohV3Yz7movvXIlD7ztfqhXd5pi+3fNZlgPr\n" +
		"Pm9hNyu2KPZVn1maeL9QBoeqf0l2wFYtQSlW+JieGKY1W9gVl4JeD8h1ND7HghF2\n" +
		"Jc2/mER7AgMBAAECggEBAOXwDHL1d9YEuaTOQSKqhLAXQ+yZWs/Mf0qyfAsYf5Bm\n" +
		"W+NZ3xJZgY3u7XnTse+EXk3d2smhVTc7XicNjhMVABouUn1UzfkACldovJjURGs3\n" +
		"u70Asp3YtTBiEzsqbnf07jJQViKQTacg+xwSwDmW2nE6BQYJjtvt7Pk20PqcvVkp\n" +
		"q7Dto1eZUC+YlNy4/FaaiS0XeAMkorbDFm40ZwkTS4VAQbhncGtY/vKg25Ird2KL\n" +
		"aOaWk8evQ78qc9C3Mjd6C6F7RPBR6b95hJ3LMzJXH9inCTPC1gvexHmTSj2spAu2\n" +
		"8vN8Cp0HEG6tyLNpoD8vQciACY6K3UYkDaxozFNU82ECgYEA9+C/Wh5nGDGai2IJ\n" +
		"wxcURARZ+XOFZhOxeuFQi7PmMW5rf0YtL31kQSuEt2vCPysMNWJFUnmyQ6n3MW+V\n" +
		"gAezTGH3aOLUTtX/KycoF+wys+STkpIo+ueOd0yg9169adWSAnmPEW42DGQ4sy4b\n" +
		"2LncHjIy8NMJGIg8xD743aIsNpECgYEA72//+ZTx5WRBqgA1/RmgyNbwI3jHBYDZ\n" +
		"xIQgeR30B8WR+26/yjIsMIbdkB/S+uGuu2St9rt5/4BRvr0M2CCriYdABgGnsv6T\n" +
		"kMrMmsq47Sv5HRhtj2lkPX7+D11W33V3otA16lQT/JjY8/kI2gWaN52kscw48V1W\n" +
		"CoPMMXFTyEsCgYEA0OuvvEAluoGMdXAjNDhOj2lvgE16oOd2TlB7t9Pf78fWeMZo\n" +
		"LT+tcTRBvurnJKCewJvcO8BwnJEz1Ins4qUa3QUxJ0kPkobRc8ikBU3CCldcfkwM\n" +
		"mDT0od6HSRej5ADq+IUGLbXLfjQ2iecR91/ng9fhkZL9dpzVQr6kuQEH7NECgYB/\n" +
		"QBjcfeopLaUwQjhvMQWgd4rcbz3mkNordMUFWYPt9XRmGi/Xt96AU8zA4gjwyKxi\n" +
		"b1l9PZnSzlGjezmuS36e8sB18L89g8rNMtqWkZLCiZI1glwH0c0yWaGQbNzUmcth\n" +
		"PiLJTLHqlxkGYJ3xsPSLBj8XNyA0NpSZtf35cO9EDQKBgQCQTukg+UTvWq98lCCg\n" +
		"D16bSAgsC4Tg+7XdoqImd9+3uEiNsr7mTJvdPKxm+jIOdvcc4q8icru9dsq5TghK\n" +
		"DEHZsHcdxjNAwazPWonaAbQ3mG8mnPDCFuFeoUoDjNppKvDrbbAOeIArkyUgTS0g\n" +
		"Aoo/jLE0aOgPZBiOEEa6G+RYpg==\n" +
		"";

	/**
	 * The AirTunes private key as an instance of {@link java.security.interfaces.RSAPrivateKey}
	 */
	public static final RSAPrivateKey PrivateKey = rsaPrivateKeyDecode(PrivateKeyData);

private static RSAPrivateKey rsaPrivateKeyDecode(final String privateKey) {
		try {
			final KeyFactory keyFactory = KeyFactory.getInstance("RSA");
			final KeySpec ks = new PKCS8EncodedKeySpec(Base64.decodePadded(privateKey));
			return (RSAPrivateKey)keyFactory.generatePrivate(ks);
		}
		catch (final Exception e) {
			throw new RuntimeException("Failed to decode built-in private key", e);
		}
	}
public static void main(String[] args) throws Exception{

 

System.out.print("Attempting to get a Blowfish key...");


//Cipher cipher=Cipher.getInstance("RSA/None/OAEPWithSHA1AndMGF1Padding");
Cipher rsaPkCS1PaddingCipher=null;
		String transformation = "RSA/None/PKCS1Padding";
	//	String transformation = "RSA";
        try {
        	rsaPkCS1PaddingCipher = Cipher.getInstance(transformation);
        	
        	System.out.println("Cipher acquired sucessfully. transformation: " + transformation);
		} 
        catch (NoSuchAlgorithmException e) {
			System.out.println("Error getting the Cipher. transformation: " + transformation);
		} 
        catch (NoSuchPaddingException e) {
        	System.out.println("Error getting the Cipher. transformation: " + transformation);
		}


//cipher.init(Cipher.ENCRYPT_MODE,key);
rsaPkCS1PaddingCipher.init(Cipher.DECRYPT_MODE,PrivateKey);
 

//byte[] cipherText=cipher.doFinal(stringToEncrypt.getBytes("UTF8"));
byte[] cipherText;//=cipher.doFinal(stringToEncrypt.getBytes("UTF8"));

System.out.println("OK");

 

System.out.println("Test completed successfully.");

}

}

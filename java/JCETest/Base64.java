//package com.amlogic.JCETest;


import java.io.IOException;
public final class Base64 {
	/**
	 * Decodes Base64 data that is correctly padded with "="
	 * 
	 * @param str base64 data
	 * @return bytes
	 * @throws IOException if the data is invalid
	 */
	public static byte[] decodePadded(final String str)
		throws IOException
	{
		return net.iharder.Base64.decode(str);
	}

	/**
	 * Decodes Base64 data that is not padded with "="
	 * 
	 * @param str base64 data
	 * @return bytes
	 * @throws IOException if the data is invalid
	 */
	public static byte[] decodeUnpadded(String base64)
		throws IOException
	{
		while (base64.length() % 4 != 0)
			base64 = base64.concat("=");

		return net.iharder.Base64.decode(base64);
	}

	/**
	 * Encodes data to Base64 and padds with "="
	 * 
	 * @param data data to encode
	 * @return base64 encoded string
	 */
	public static String encodePadded(final byte[] data)
	{
		return net.iharder.Base64.encodeBytes(data);
	}

	/**
	 * Encodes data to Base64 but doesn't pad with "="
	 * 
	 * @param data data to encode
	 * @return base64 encoded string
	 */
	public static String encodeUnpadded(final byte[] data)
	{
		String str = net.iharder.Base64.encodeBytes(data);

		final int pad = str.indexOf('=');
		if (pad >= 0)
			str = str.substring(0, pad);

		return str;
	}
}


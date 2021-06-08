package application.comm;

import java.io.FileInputStream;
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketTimeoutException;
import java.util.Properties;

public class UDPClient {
	
	
	private Properties _properties;
	
	public UDPClient(Properties properties) {
		_properties = properties;
		
	}
	
	
	public void send(byte[] data) {
		String hostname = _properties.getProperty("client.ip", "127.0.0.1");
        int port = Integer.parseInt(_properties.getProperty("client.port","9090"));
 
        try {
            InetAddress address = InetAddress.getByName(hostname);
            DatagramSocket socket = new DatagramSocket();
//            while (true) {
 
                DatagramPacket request = new DatagramPacket(data, data.length, address, port);
                socket.send(request);
 
//                byte[] buffer = new byte[512];
//                DatagramPacket response = new DatagramPacket(buffer, buffer.length, );
//                socket.receive(response);
// 
//                String quote = new String(buffer, 0, response.getLength());
// 
//                System.out.println(quote);
//                System.out.println();
// 
//                Thread.sleep(10000);
//            }
                socket.close();
        } catch (SocketTimeoutException ex) {
            System.out.println("Timeout error: " + ex.getMessage());
            ex.printStackTrace();
        } catch (IOException ex) {
            System.out.println("Client error: " + ex.getMessage());
            ex.printStackTrace();
        } 
//        catch (InterruptedException ex) {
//            ex.printStackTrace();
//        }
	}

}

package application.test;

import java.io.*;
import java.net.*;
import java.util.*;

import application.util.DispayUtil;
 
/**
 * This program demonstrates how to implement a UDP server program.
 *
 *
 * @author www.codejava.net
 */
public class TestUDPServer {
    private DatagramSocket socket;
    private List<String> listQuotes = new ArrayList<String>();
    private Random random;
 
    public TestUDPServer(int port) throws Exception {
    	InetAddress address = InetAddress.getByName("127.0.0.1");
        socket = new DatagramSocket(port,address);
        random = new Random();
    }
 
    public static void main(String[] args) {
//        if (args.length < 2) {
//            System.out.println("Syntax: QuoteServer <file> <port>");
//            return;
//        }
 
//        String quoteFile = args[0];
        int port = Integer.parseInt("9090");
 
        try {
        	TestUDPServer server = new TestUDPServer(port);
 //           server.loadQuotesFromFile(quoteFile);
            server.service();
        } catch (SocketException ex) {
            System.out.println("Socket error: " + ex.getMessage());
        } catch (IOException ex) {
            System.out.println("I/O error: " + ex.getMessage());
        } catch (Exception ex) {
            System.out.println("Exception error: " + ex.getMessage());
        }
    }
 
    private void service() throws IOException {
        while (true) {
        	byte[] buffer = new byte[512];
            DatagramPacket request = new DatagramPacket(buffer, buffer.length);
            socket.receive(request);
 
            String received = new String(request.getData(), 0, request.getData().length);
            System.out.println(received);
            System.out.println("HEX = " + DispayUtil.toHexString(request.getData()));
//            String quote = getRandomQuote();
//            byte[] buffer = quote.getBytes();
// 
//            InetAddress clientAddress = request.getAddress();
//            int clientPort = request.getPort();
// 
//            DatagramPacket response = new DatagramPacket(buffer, buffer.length, clientAddress, clientPort);
//            socket.send(response);
        }
    }
 
    private void loadQuotesFromFile(String quoteFile) throws IOException {
        BufferedReader reader = new BufferedReader(new FileReader(quoteFile));
        String aQuote;
 
        while ((aQuote = reader.readLine()) != null) {
            listQuotes.add(aQuote);
        }
 
        reader.close();
    }
 
    private String getRandomQuote() {
        int randomIndex = random.nextInt(listQuotes.size());
        String randomQuote = listQuotes.get(randomIndex);
        return randomQuote;
    }
}

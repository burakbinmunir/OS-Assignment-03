/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package cs;

/**
 *
 * @author Mr Rabbani
 */
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.Scanner;

public class l201302_Client {
    private Socket socket;
    private Scanner scanner;
    private PrintWriter printer;
    private BufferedReader reader;
    private String host;
    private int port;
    
    l201302_Client() throws IOException{
        host = "localhost";
        port = 1302;
        try {
            socket = new Socket(host, port);
            
            reader = new BufferedReader(new InputStreamReader(socket.getInputStream())); // for reading messages from server
            printer = new PrintWriter(socket.getOutputStream(), true); // for sending message to server
            scanner = new Scanner(System.in);
            
            String message = "Message";
            while (!message.equals("close")) {
                // sending message to server
                System.out.println("Enter Message for Server: ");
                message = scanner.nextLine();
                printer.println(message);              
                printer.flush();
                
                // receiving message from server and printing
                System.out.println("Message from Server: " + reader.readLine());
                System.out.println();
            }
        }
        catch (IOException e){
            e.printStackTrace();
        }
        finally{
            scanner.close();
            reader.close();
            printer.close();
            socket.close();
        }
    }

    public static void main(String[] args) throws IOException {
        l201302_Client client = new l201302_Client(); // invoking client
    }
}


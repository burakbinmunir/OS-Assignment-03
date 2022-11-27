/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package cs;

/**
 *
 * @author Shehryar Munir 
 */
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;

class ClientHandler implements Runnable {

    private Socket clientSocket;
    private PrintWriter serverPrinter;
    private BufferedReader serverReader;
    private int clientNumber;
    // setting new Client
    ClientHandler(Socket clientSocket, int clientNumber){
        this.clientSocket = clientSocket;
        System.out.println("This is client: " + clientSocket.getInetAddress().getHostName());
        this.clientNumber = clientNumber;
    }
    
    // everytime thread will start this method will be called
    @Override
    public void run() {
        try{
            serverReader = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
            serverPrinter  = new PrintWriter(new OutputStreamWriter(clientSocket.getOutputStream()));
            String clientMessage;
            while ((clientMessage = serverReader.readLine()) != null) {
                System.out.println(clientMessage + " from Client " + clientNumber);
                
                /*
                    For implementing 2 way communication server will send back
                    message to client, for the sake of simplicity the receievd
                    message will be sent back to the cleint
                */
                System.out.println("Sending message to client " + clientNumber);
                serverPrinter.println(clientMessage);
                serverPrinter.flush();
            }
        }
        catch (Exception exception) {
            exception.printStackTrace();
        }
        finally {
            try {
            serverReader.close();
            serverPrinter.close();
            }
            catch (IOException ioException){
                ioException.printStackTrace();
            }
        }
    }
    
}

public class l201302_Server extends Thread {
    private ServerSocket serverSocket;
    private int port;
    l201302_Server()  {
        port = 1302;
        try {

            serverSocket = new ServerSocket(port);
            if (serverSocket == null)
                return;
            serverSocket.setReuseAddress(true);
            System.out.println("Server is running");
            
            int index = 0;
            while(true){
                Socket clientSocket = serverSocket.accept();
                
                ClientHandler newClient = new ClientHandler(clientSocket, index);
                
                /*
                    Every time there comes a new client it will be handled
                    as a separate client by the server with the help of 
                    client handler class
                */
                Thread thread = new Thread(newClient);
                thread.setName("Client: " + index);
                System.out.println("\t\t\t\tStarted: " + thread.getName());
                System.out.println();
                
                thread.start();
                index++;
            }
            
        }
        catch (IOException e){
            e.printStackTrace();
        }
        finally{
            if (serverSocket != null){
                try {
                    serverSocket.close();
                }
                catch(Exception es){
                    es.printStackTrace();
                }
            }
        }
    }

    public static void main(String[] args) {
        l201302_Server server = new l201302_Server(); // invoking server
    }
}

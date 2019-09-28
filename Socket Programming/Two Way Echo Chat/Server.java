import java.net.Socket;
import java.net.ServerSocket;
import java.io.IOException;
import java.io.PrintWriter;

import java.util.Scanner;
import java.util.concurrent.Executors;


// A simple TCP server.

public class Server{

    public static void main(String[] args) {
        try { 
            
            ServerSocket soc = new ServerSocket(25000);     // Creates a Server Socket 
            System.out.println("Server Running ....");
            var pool = Executors.newFixedThreadPool(3);    // var compiler determines type
//  var :   java.util.concurrent.ExecutorService pool = Executors.newFixedThreadPool(20);
// only allows 3 concurrent communication and all other requests are saved in queue.
            while(true){
                pool.execute(new DoWork(soc.accept()));
            }

        }catch(IOException ioe){
            System.out.println("Error   : Server Intialization Failed");
            System.out.println("Message : "+ioe.getMessage() );
        }

    }

    public static class DoWork implements Runnable {
        private Socket socket ;
        
        DoWork(Socket socket){
            this.socket = socket ; 
        }

        @Override
        public void run(){
            System.out.println("Connected : "+ socket );
            try{
                var in  = new Scanner(socket.getInputStream());
                var out = new PrintWriter(socket.getOutputStream(),true);
                while( in.hasNextLine() ){
                    out.println(in.nextLine());
                }
            }catch(IOException ioe){
                System.out.println("Error : "+ioe.getMessage());
            }finally {
                try {
                    socket.close();
                }catch(IOException ioe){
                    System.out.println("Error Closing Socket : "+ioe.getMessage());
                }
            }
        }

    }
    
}

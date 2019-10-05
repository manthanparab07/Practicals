import java.net.Socket;
import java.net.ServerSocket;
import java.io.IOException;
import java.io.PrintWriter;

// A simple TCP server.

public class Server{

    public static void main(String[] args) {
        try { 
            ServerSocket soc = new ServerSocket(25000);     // Creates a Server Socket 
            System.out.println("Server Running ....");
            while(true){
                
                Socket socket = soc.accept() ;      // A Blocking Call which listen's for indefinitely 
                System.out.println("Connection Established at Port : "+ soc.getLocalPort() );
                PrintWriter out = new PrintWriter(socket.getOutputStream(),false);  // autooflush : false 
                out.println("Hello From Server".toString());        // write message into stream
                out.flush();        // as autoflush is turned off explicit flush required to send data
            }
            // soc.close();         // to free up resources 
            // needed only when while loop is exited after doing required job and to explicit free up the resources. 
        }catch(IOException ioe){
            System.out.println("Error   : Server Intialization Failed");
            System.out.println("Message : "+ioe.getMessage() );
        }

    }
    
}

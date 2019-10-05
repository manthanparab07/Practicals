import java.io.IOException;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.Scanner;


/**
 * A simple Swing-based client for the chat server. Graphically it is a frame with a text
 * field for entering messages and a textarea to see the whole dialog.
 *
 * The client follows the following Chat Protocol. When the server sends "SUBMITNAME" the
 * client replies with the desired screen name. The server will keep sending "SUBMITNAME"
 * requests as long as the client submits screen names that are already in use. When the
 * server sends a line beginning with "NAMEACCEPTED" the client is now allowed to start
 * sending the server arbitrary strings to be broadcast to all chatters connected to the
 * server. When the server sends a line beginning with "MESSAGE" then all characters
 * following this string should be displayed in its message area.
 */

// Java code for thread creation by extending 
// the Thread class 
class doRecieve extends Thread 
{   Socket socket;
    Scanner in;
    PrintWriter out;
    Scanner inp;
    boolean loggedIN ;

    public doRecieve(Socket socket,Scanner in , PrintWriter out , Scanner inp ){
        this.socket = socket ;
        this.in = in ;
        this.out = out ;
        this.inp = inp ;
        this.loggedIN = false ;
    }

	public void run() 
	{ 
		while(in.hasNextLine()){
            var line = in.nextLine();
            if (line.startsWith("SUBMITNAME")) {
             System.out.print("Submit Name : ");
             out.println(inp.nextLine());
         } else if (line.startsWith("NAMEACCEPTED")) {
             System.out.println("-- Connected -- ");
             System.out.println("Chatter - " + line.substring(13) );
             if(!loggedIN){
                doSent ds = new doSent(socket, in, out, inp);
                ds.start();
             }
             
         } else if (line.startsWith("MESSAGE")) {
             System.out.println(" ---- "+ line.substring(8) + "\n");
         }
                }
	} 
} 

class doSent extends Thread 
{   Socket socket;
    Scanner in;
    PrintWriter out;
    Scanner inp;

    public doSent(Socket socket,Scanner in , PrintWriter out , Scanner inp ){
        this.socket = socket ;
        this.in = in ;
        this.out = out ;
        this.inp = inp ;
    }

	public void run() 
	{ 
		while(true){
            out.println(inp.nextLine());
        }
	} 
} 

public class Client {
    
    /**
     * Constructs the client by laying out the GUI and registering a listener with the
     * textfield so that pressing Return in the listener sends the textfield contents
     * to the server. Note however that the textfield is initially NOT editable, and
     * only becomes editable AFTER the client receives the NAMEACCEPTED message from
     * the server.
     */

    public static void main(String[] args) throws IOException {

            var socket = new Socket("127.0.0.1", 25000);
            Scanner in = new Scanner(socket.getInputStream());
            PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
            Scanner inp = new Scanner(System.in);
            
            doRecieve dr = new doRecieve(socket, in, out, inp);
            dr.start();
                
        
        }

}
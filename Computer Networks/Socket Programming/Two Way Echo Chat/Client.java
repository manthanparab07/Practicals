import java.net.Socket;
import java.io.IOException;
import java.util.Scanner;
import java.io.PrintWriter;

public class Client{
    public static void main(String[] args) {
        try {
            Socket soc = new Socket("127.0.0.1",25000);     // Create a Socket to listen at port 25000 for IP 127.0.0.1
            System.out.println("Enter lines of text then Ctrl+D or Ctrl+C to quit");
            System.out.println("Socket : "+ soc);
            Scanner scr = new Scanner(soc.getInputStream());    // reading from network stream
            Scanner inp = new Scanner(System.in);  // getting text from keyboard

            PrintWriter out = new PrintWriter(soc.getOutputStream(),true);

            while( inp.hasNextLine()){
                out.println(inp.nextLine());
                System.out.println(scr.nextLine());
            }

            System.out.println("Message : " + scr.nextLine());
            scr.close();    // Close Scanner
            soc.close();    // Close Socket
        }catch(IOException ioe){
            System.out.println("Error   : Failed to Connect");
            System.out.println("Message : "+ioe.getMessage());
        }
    }
}

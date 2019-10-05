import java.net.Socket;
import java.io.IOException;
import java.util.Scanner;

public class Client{
    public static void main(String[] args) {
        try {
            Socket soc = new Socket("127.0.0.1",25000);     // Create a Socket to listen at port 25000 for IP 127.0.0.1
            Scanner scr = new Scanner(soc.getInputStream());
            System.out.println("Message : " + scr.nextLine());
            scr.close();    // Close Scanner
            soc.close();    // Close Socket
        }catch(IOException ioe){
            System.out.println("Error   : Failed to Connect");
            System.out.println("Message : "+ioe.getMessage());
        }
    }
}

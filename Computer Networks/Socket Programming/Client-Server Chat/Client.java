import java.net.Socket;
import java.net.ServerSocket;
import java.io.IOException;
import java.util.Scanner;
import java.io.PrintWriter;

public class Client{
    public static void main(String[] arg) throws IOException {
        Socket soc = new Socket("127.0.0.1",25000);
        System.out.println(soc);
        System.out.println("Connection Established : " + soc.getLocalPort() );
        String input ;
        Scanner in = new Scanner(soc.getInputStream());
        Scanner inp = new Scanner(System.in);
        PrintWriter out = new PrintWriter(soc.getOutputStream(),true);
        while(true){
            
            input = in.nextLine();
            
            if (input.toLowerCase().startsWith("quit")) {
                out.println("quit");
                break;
            }else{
                System.out.println("Message  : "+ input );
                System.out.print("Response : ");
                out.println(inp.nextLine());
            }
    
        }
        System.out.println("Server Closed ..");
        soc.close();
    }
}
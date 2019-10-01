import java.net.Socket;
import java.net.ServerSocket;
import java.io.IOException ;
import java.io.PrintWriter;
import java.util.Scanner;

public class Server{
    public static void main(String[] args) throws IOException{
        ServerSocket serv = new ServerSocket(25000);
        System.out.println(serv);
        System.out.println("Server Running ...");
        String input ;
        Socket soc = serv.accept();
        System.out.println("Connected : "+ soc);
        Scanner in = new Scanner(soc.getInputStream());
        Scanner inp = new Scanner(System.in);
        PrintWriter out = new PrintWriter(soc.getOutputStream(),true);
        out.println("Hi What's Up !!");
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
        serv.close();
    }
}
import java.net.InetAddress;
import java.util.Scanner;
import java.io.IOException;

public class DNS_Lookup{

	public static Scanner inp ;
	public static InetAddress inet ;
	public static String url ;
	
	public static void main(String args[]){
		try{
			System.out.print("Enter Website Name : ");
			inp = new Scanner(System.in);
			url = inp.nextLine();
			inet = InetAddress.getByName( url );

			System.out.println( "Website Information : " + inet);
			InetAddress arr[] = InetAddress.getAllByName(url);
			for( InetAddress i : arr ){
				display(i);
			}
		}catch(IOException e){
			System.out.println(e.getMessage());
		}
		

	}

	public static void display(InetAddress inet ){
		System.out.println(" ---------------------");
		System.out.println( "Canonical Host Name : " + inet.getCanonicalHostName() );
		System.out.println( "Host Name : " + inet.getHostName() );
		System.out.println( "Host Address : " + inet.getHostAddress() );
	}

}

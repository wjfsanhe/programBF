import java.net.MulticastSocket;
import java.net.NetworkInterface;
import java.net.*;
import java.util.Collections;
import java.util.Formatter;

class  MulticastNet {

	public static void main(String[]arg)
		throws Exception
		{
			InetAddress localHost=InetAddress.getLocalHost();
			System.out.println("IP:"+localHost.toString());
			for(final NetworkInterface iface: Collections.list(NetworkInterface.getNetworkInterfaces())) {
				if(iface.isLoopback()) 
				{
					System.out.println("loopback:");


				}
				if(iface.isPointToPoint() )
				{
					System.out.println("p2p:");
				}


				System.out.println(iface.toString() + " status:" + (iface.isUp()?"up":"down"));
				int i=0;
				for(final InetAddress addr: Collections.list(iface.getInetAddresses())) {
					if(addr instanceof Inet4Address)		
						System.out.println("----addrIPV4"+":"+addr.toString()+"HostName:"+addr.getHostName());
					if(addr instanceof Inet6Address)		
						System.out.println("----addrIPv6"+":"+addr.toString()+"HostName:"+addr.getHostName());
				
					if(iface.supportsMulticast())
					{
					System.out.println("join mdns Group");
					InetAddress group;
					group = InetAddress.getByName("224.0.0.251");
					MulticastSocket socket;
					socket=new MulticastSocket(5353);
					socket.setNetworkInterface(iface);
					socket.setTimeToLive(255);
					socket.joinGroup(group);
					String  str=new String("Hello");
					DatagramPacket packet=new DatagramPacket(str.getBytes(),str.length(),group,5353);
					socket.send(packet);
					socket.leaveGroup(group);
					socket.close();	
					}
				}
			}
		}

}

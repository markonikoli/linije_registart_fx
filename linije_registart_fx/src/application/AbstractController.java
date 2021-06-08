package application;

import java.io.FileInputStream;
import java.util.Properties;

import application.comm.UDPClient;
import application.util.DispayUtil;

public abstract class AbstractController {
	
	private static Properties properties = null;
	
	

	
	
	
	private static void load_resource_properties() {
		properties = new Properties();
        try {
            FileInputStream stream = new FileInputStream(
                    "application.properties");
            properties.load(stream);
            stream.close();
        } catch (Exception e) {
            System.out.println(
                    "Unable to load properties from application.properties file, details: " + e.getMessage());
        }
	}
	
	protected static Properties getProperties() {
		if(properties == null) {
			load_resource_properties();
		}
		return properties;
	}
	
	protected abstract byte[] set_for_dispay();
	
	
	protected void send_to_displays() {
		new UDPClient(getProperties()).send(set_for_dispay());
	}
	
	protected void set_mode_to_auto() {
		new UDPClient(getProperties()).send(DisplaySettings.get_auto_mode());
	}
}

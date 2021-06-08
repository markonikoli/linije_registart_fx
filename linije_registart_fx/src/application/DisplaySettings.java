package application;

import java.nio.ByteBuffer;

public class DisplaySettings {
	
	
	public static final String SWITCHING_TIME_KEY = "SWITCHING_TIME";
	public static final String DISPLAY_MODE_KEY = "DISPLAY_MODE";
	public static final String DISPLAY_SIDE_KEY = "DISPLAY_1";
	public static final String DISPLAY_FRONT_KEY = "DISPLAY_2";
	public static final String DISPLAY_BACK_KEY = "DISPLAY_3";
	
	
	
	private static final String DISPLAY_MODE_VALUE_MANUAL = "M";
	private static final String DISPLAY_MODE_VALUE_AUTO = "A";
	
	private static final String KEY_VALUE_SEPARATOR = "=";
	private static final String PARAM_SEPARATOR = ";";
	
	
	private ByteBuffer bbuf = ByteBuffer.allocate(1000);
	
	//private boolean is_set = false;
	
	private String _switching_time= "";
	
	public DisplaySettings(int switching_time) {
		_switching_time = "" + switching_time;
	}
	
	public void addForDisplay(String key, byte[] value) {
		
		//String to_add = is_set ? PARAM_SEPARATOR : "";
		
		String to_add =  key + KEY_VALUE_SEPARATOR;
		//is_set = true;
		bbuf.put(to_add.getBytes());
		bbuf.put(value);
		bbuf.put(PARAM_SEPARATOR.getBytes());
		
	}
	
	public static byte[] get_auto_mode() {
		String to_return = DISPLAY_MODE_KEY + KEY_VALUE_SEPARATOR + DISPLAY_MODE_VALUE_AUTO;
		return to_return.getBytes();
	}
	
	private void addManual_mode() {
		addForDisplay(DISPLAY_MODE_KEY, DISPLAY_MODE_VALUE_MANUAL.getBytes());
	}
	
	private void addSwitchingTime() {
		addForDisplay(SWITCHING_TIME_KEY, _switching_time.getBytes());
	}
	
	
	public byte[] getForDisplays() {
		addManual_mode();
		addSwitchingTime();
		return bbuf.array();
	}

}

	
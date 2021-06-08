package application.util;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;


public class InputFileReader {
	
	private static LineWithNumberCollection _lines_with_num = null;
	private static LineWithoutNumberCollection _lines_without_num =null;
	
	public static  AbstractLineColleaction getCollection() {
		
		if(_lines_with_num != null) {
			return _lines_with_num;
		}
		if(_lines_without_num != null) {
			return _lines_without_num;
		}
		BufferedReader reader;
		try {
			reader = new BufferedReader(new FileReader(
					"linije.csv"));
			String line = reader.readLine();
			boolean is_first_line = true;
			while (line != null) {
				System.out.println(line);
				//skip first line
				if(is_first_line) {
					is_first_line = false;
					continue;
				}
				// read next line
				addLineInCollection(line.split(","));
				line = reader.readLine();
				
			}
			reader.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
		if(_lines_with_num != null) {
			return _lines_with_num;
		}else {
			return _lines_without_num;
		}
	}
	
	private static void addLineInCollection(String[] parsed) {
		System.out.println("parsed.length" + parsed.length + ", parsed" + parsed);
			if(parsed.length == 2) {
				//line without number
				addLineWithoutNum(parsed[0], parsed[1]);
			}
			if(parsed.length == 4) {
				//line with number
				addLineWitNum(parsed[0], parsed[1],parsed[2], parsed[3]);
			}

	}
	
	
	private static void addLineWithoutNum(String pocetno_stajaliste, String krajnje_stajaliste) {
		if(_lines_without_num == null) {
			_lines_without_num = new LineWithoutNumberCollection();
		}
		_lines_without_num.addLine(new LineData(pocetno_stajaliste, krajnje_stajaliste));
	}
	
	private static void addLineWitNum(String line_num, String route_num, String pocetno_stajaliste, String krajnje_stajaliste) {
		if(_lines_with_num == null) {
			_lines_with_num = new LineWithNumberCollection();
		}
		String[] line_subline = getLineNumSubline(line_num).split(":");
		int line_number = Integer.parseInt(line_subline[0]);
		if(line_number > 0) {
		_lines_with_num.addLine(new LineDataWithNumber(line_number, line_subline.length> 1 ? line_subline[1] : "", pocetno_stajaliste, krajnje_stajaliste));
		}
	}
	
	

	
	private static String getLineNumSubline(String line_num) {
		if(is_number(line_num)) {
			return line_num + ":" + "";
		}else {
			//moze da bude max 3 broja
			
				String stotice = line_num.substring(0,1);
				if(is_number(stotice)) {
					String desetice = line_num.substring(1,2);
					if(is_number(desetice)) {
						String jedinice = line_num.substring(2,3);
						if(is_number(jedinice)) {
							return stotice + desetice + jedinice + ":" + line_num.substring(3);
						}else {
							return stotice + desetice + ":" + line_num.substring(2);
						}
					}else {
						return stotice + ":" + line_num.substring(1);
					}
				}else {
					//ako je prvi broj, to ne podrzavamo
					return "" + 0 + ":" + "";
				}
			
		}
	}
	
	private static boolean is_number(String line_num) {
		try {
			Integer.parseInt(line_num);
			return true;
		}catch(Throwable e) {
			return false;
		}
	}
	
	
	

}

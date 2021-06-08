package application.util;

import java.util.*;
import java.util.Map.Entry;

public class LineWithNumberCollection extends AbstractLineColleaction{
	
	private Map<Integer, List<LineDataWithNumber>> _lines = new HashMap<Integer, List<LineDataWithNumber>>();
	
	public void addLine(LineDataWithNumber line) {
		List<LineDataWithNumber> lines_lst = _lines.get(Integer.valueOf(line.get_line_number()));
		if(lines_lst == null) {
			lines_lst = new ArrayList<LineDataWithNumber>();
			_lines.put(Integer.valueOf(line.get_line_number()), lines_lst);
		}
		lines_lst.add(line);
	}
	
	@SuppressWarnings("unchecked")
	public List<LineDataWithNumber> getAllLines(){
		List<LineDataWithNumber> to_return = new ArrayList<LineDataWithNumber>();
		for(Entry<Integer, List<LineDataWithNumber>> entry : _lines.entrySet()) {
			to_return.addAll(entry.getValue());
		}

		return to_return;
	}
	
	
	public List<LineDataWithNumber> getLines(int line_number){
		List<LineDataWithNumber> to_return = new ArrayList<LineDataWithNumber>();
		if(_lines.get(Integer.valueOf(line_number)) != null) {
			to_return = _lines.get(Integer.valueOf(line_number));
		}
		return to_return;
	}
	
	public boolean is_line_with_sublines(int line_number) {
		List<LineDataWithNumber> lines = getLines(line_number);
		
		for(LineDataWithNumber current: lines) {
			if(current.get_sub_line() != "") {
				return true;
			}
		}
		
		return false;
	}
	
	public List<String> getSublines(int line_number){
		List<String> to_return = new ArrayList<String>();
		List<LineDataWithNumber> lines = getLines(line_number);
		for(LineDataWithNumber current : lines) {
			if(!current.get_sub_line().equals("")) {
				to_return.add(current.get_sub_line());
			}
		}
		
		return to_return;
	}
	
	public List<String> getPocetnoKrajnjeStajaliste(int line_number, String subline){
		
		System.out.println("getPocetnoKrajnjeStajaliste, line_number = " + line_number + ", subline = " + subline);
		List<String> to_return = new ArrayList<String>();
		List<LineDataWithNumber> lines = getLines(line_number);
		
		for(LineDataWithNumber current : lines) {
			if(current.get_sub_line().equals(subline)) {
				to_return.add(current.get_pocetno_stajaliste());
				to_return.add(current.get_krajnje_stajaliste());
				break;
			}
		}
		
		return to_return;
	}

}

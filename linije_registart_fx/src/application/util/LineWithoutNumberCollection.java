package application.util;

import java.util.*;

public class LineWithoutNumberCollection extends AbstractLineColleaction{
	
	private Map<String, List<LineData>> _lines = new HashMap<String, List<LineData>>();
	
	
	
	
	public void addLine(LineData line) {
		List<LineData> lines_lst = _lines.get(line.get_pocetno_stajaliste());
		if(lines_lst == null) {
			lines_lst = new ArrayList<LineData>();
			_lines.put(line.get_pocetno_stajaliste(), lines_lst);
		}
		lines_lst.add(line);
	}
	
	
	public List<LineData> getLines(String pocetno_stajaliste){
		return _lines.get(pocetno_stajaliste);
	}
	
	public List<String> getKrajnjaStajalista(String pocetno_stajaliste){
		List<String> to_return = new ArrayList<String>();
		List<LineData> linije = getLines(pocetno_stajaliste);
		for(LineData current: linije) {
			to_return.add(current.get_krajnje_stajaliste());
		}
		return to_return;
	}
	
	public Set<String> getPocetnaStajalista(){

		return _lines.keySet();
	}
	
	

}

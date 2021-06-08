package application;

import java.net.URL;
import java.util.ArrayList;
import java.util.List;
import java.util.ResourceBundle;

import application.util.InputFileReader;
import application.util.LineDataWithNumber;
import application.util.LineWithoutNumberCollection;
import application.util.DispayUtil;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.geometry.Pos;
import javafx.scene.control.Button;
import javafx.scene.control.ChoiceBox;
import javafx.scene.control.ComboBox;
import javafx.scene.control.Label;
import javafx.scene.control.ListCell;
import javafx.scene.control.ListView;
import javafx.scene.layout.AnchorPane;
import javafx.scene.paint.Paint;
import javafx.util.Callback;

public class NoLineNumUIController extends AbstractController implements Initializable{
	
	@FXML private AnchorPane root_pane;
	@FXML private Button osvezi_btn;
	@FXML private Button prihvati_btn;
	@FXML private Button izmeni_smer_btn;
//	@FXML private ChoiceBox<String> pocetna_cbx;
//	@FXML private ChoiceBox<String> krajnja_cbx;
	@FXML private Label disp_line_title_lbl;
	@FXML private Label linija_od_gore_lbl;
	@FXML private Label linija_do_gore_lbl;
	@FXML private Label linija_od_dole_lbl;
	@FXML private Label linija_do_dole_lbl;
	@FXML private Button direction_btn;
	@FXML private Button direction_dole_btn;
	@FXML private Button goToIzaberiLiniju_btn;
	@FXML private ComboBox<String> od_cmb;
	@FXML private ComboBox<String> do_cmb;
	@FXML private Button goToIzaberiLinijuVeliko_btn;
	@FXML private Button otkazi_btn;
	
	
	private LineWithoutNumberCollection _line_data = null;
	
	
	
	private String _display_smer_A = "";
	private String _display_smer_B = "";
	
	private String _current_display = "";
	
	List<String> krajnja_stajalista = new ArrayList<String>();
	
    @Override
    public void initialize(URL location, ResourceBundle resources) {
    	osvezi_btn.setVisible(false);
    	//init_do_combo_list_size();
    	display_home_screen();
        //tableView.getItems().addAll(getDataFromSource());
    	_line_data = (LineWithoutNumberCollection)InputFileReader.getCollection();
    	//pocetna_cbx.getItems().addAll(_line_data.getPocetnaStajalista());
    	od_cmb.getItems().addAll(_line_data.getPocetnaStajalista());
    	setSelectionListeners(); 
    	display_init_screen();
    }
    
	private void display_init_screen() {
		root_pane.setStyle("-fx-background-image: url('/application/pics/background_blue_up.gif')");
		linija_od_gore_lbl.setAlignment(Pos.CENTER_RIGHT);
		linija_do_gore_lbl.setAlignment(Pos.CENTER_LEFT);
		linija_od_dole_lbl.setAlignment(Pos.CENTER_RIGHT);
		linija_do_dole_lbl.setAlignment(Pos.CENTER_LEFT);

		prihvati_btn.setVisible(false);
		od_cmb.setVisible(false);
		do_cmb.setVisible(false);
		izmeni_smer_btn.setVisible(false);
		direction_btn.setVisible(false);
		direction_dole_btn.setVisible(false);
		disp_line_title_lbl.setVisible(false);

		linija_od_gore_lbl.setVisible(false);
		linija_do_gore_lbl.setVisible(false);
		linija_od_dole_lbl.setVisible(false);
		linija_do_dole_lbl.setVisible(false);
		goToIzaberiLiniju_btn.setVisible(false);
		goToIzaberiLinijuVeliko_btn.setVisible(true);
		otkazi_btn.setVisible(false);
	}
	
	
	private void display_home_screen() {
		root_pane.setStyle("-fx-background-image: url('/application/pics/background_blue_up.gif')");
		linija_od_gore_lbl.setAlignment(Pos.CENTER_RIGHT);
		linija_do_gore_lbl.setAlignment(Pos.CENTER_LEFT);
		linija_od_dole_lbl.setAlignment(Pos.CENTER_RIGHT);
		linija_do_dole_lbl.setAlignment(Pos.CENTER_LEFT);

		prihvati_btn.setVisible(false);
		od_cmb.setVisible(false);
		do_cmb.setVisible(false);
		izmeni_smer_btn.setVisible(true);
		direction_btn.setVisible(false);
		direction_dole_btn.setVisible(true);
		disp_line_title_lbl.setVisible(true);

		linija_od_gore_lbl.setVisible(true);
		linija_do_gore_lbl.setVisible(true);
		linija_od_dole_lbl.setVisible(true);
		linija_do_dole_lbl.setVisible(true);
		goToIzaberiLiniju_btn.setVisible(true);
		goToIzaberiLinijuVeliko_btn.setVisible(false);
		otkazi_btn.setVisible(false);
	}
	
	
	private void display_selection_screen() {
		//root_pane.setStyle("-fx-background-image: url('/application/pics/background_blue_up.gif')");
		izmeni_smer_btn.setVisible(false);
		direction_btn.setVisible(true);
		direction_dole_btn.setVisible(false);
		disp_line_title_lbl.setVisible(false);
		linija_od_gore_lbl.setVisible(false);
		linija_do_gore_lbl.setVisible(false);
		linija_od_dole_lbl.setVisible(false);
		linija_do_dole_lbl.setVisible(false);
		goToIzaberiLiniju_btn.setVisible(false);
		
		prihvati_btn.setVisible(true);
		od_cmb.setVisible(true);
		do_cmb.setVisible(true);
		goToIzaberiLinijuVeliko_btn.setVisible(false);
		otkazi_btn.setVisible(true);
	}
	
	
	
	public void handlePrihvati() {
		
		_display_smer_A = "Smer: " +  od_cmb.getValue() +  "-" + do_cmb.getValue();
		_display_smer_B = "Smer: "  + do_cmb.getValue() +  "-" + od_cmb.getValue();
		
		String[] splt_od = od_cmb.getValue().split(" ",0);
		linija_od_gore_lbl.setText(splt_od[0]);
		if(splt_od.length > 1) {
			linija_od_dole_lbl.setText(splt_od[1]);
		}else {
			linija_od_dole_lbl.setText("");
		}
		
		String[] splt_do = do_cmb.getValue().split(" ",0);
		linija_do_gore_lbl.setText(splt_do[0]);
		if(splt_do.length > 1) {
			linija_do_dole_lbl.setText(splt_do[1]);
		}else {
			linija_do_dole_lbl.setText("");
		}
		
		
		
		_current_display = _display_smer_A;
		send_to_displays();
		System.out.println("prihvati akcija");
		reset();
		
		
	}
	
	public void handleOtkazi() {
		reset();
	}
	
	private void  init_do_combo_list_size() {
		do_cmb.setCellFactory(new Callback<ListView<String>, ListCell<String>>() {
			@Override
			public ListCell<String> call(ListView<String> param) {
				ListCell cell = new ListCell<String>() {
					@Override
					public void updateItem(String item, boolean empty) {
						System.out.println("init_do_combo_list_size, item = "+item+" empty = " + empty);
						if(empty) {
							return;
						}else {
							super.updateItem(item, empty);
							int numItems = getListView().getItems().size();
							System.out.println("init_do_combo_list_size, numItems = "+numItems);
							int height = 150;    // set the maximum height of the popup
							if (numItems <= 5) height = numItems * 30;    // set the height of the popup if number of items is equal to or less than 5
							System.out.println("height = "+height);
							getListView().setPrefHeight(height);
							
							setText(item.toString());

						}

					}
				};
				return cell;
			}
		});
	}
	

	public void handleOsvezi() {
		System.out.println("ozvezi akcija");
		set_mode_to_auto();
		reset();
		System.exit(0);
	}
	
	public void handleIzmeniSmer() {
		System.out.println("izmeni smer akcija: _current_display = " + _current_display + ",\n _display_smer_A = " + _display_smer_A + "\n _display_smer_B = " + _display_smer_B);
		if(_current_display.equals(_display_smer_A)) {
			_current_display = _display_smer_B;
				
		}
		else {
			_current_display = _display_smer_A;
			
		}
		String swap_buffer = linija_do_gore_lbl.getText();
		linija_do_gore_lbl.setText(linija_od_gore_lbl.getText());
		linija_od_gore_lbl.setText(swap_buffer);
		
		swap_buffer = linija_do_dole_lbl.getText();
		linija_do_dole_lbl.setText(linija_od_dole_lbl.getText());
		linija_od_dole_lbl.setText(swap_buffer);
		send_to_displays();
	}
	
	public void goToIzaberiLiniju() {
		display_selection_screen();
	}
    
    private void reset() {
    	do_cmb.getItems().clear();
    	do_cmb.getItems().removeAll(krajnja_stajalista);
    	do_cmb.setVisible(false);
    	display_home_screen();
    }
    
    private void setKrajnja() {
    	do_cmb.getItems().clear();
    	do_cmb.getItems().removeAll(krajnja_stajalista);
    	krajnja_stajalista = _line_data.getKrajnjaStajalista(od_cmb.getValue());
    	do_cmb.getItems().addAll(krajnja_stajalista);
    	do_cmb.setVisible(true);
    }
    
    private void setSelectionListeners() {

    	
    	
    	od_cmb.setOnAction((event) -> {
    	    boolean selected = od_cmb.getValue() != null;
    	    System.out.println("CheckBox Action (selected: " + selected + ")");
    	    if(selected) {
    	    	setKrajnja();
    	    }
    	});
    }
    
    @Override
    protected byte[]  set_for_dispay(){
    	DisplaySettings disp_sett = new DisplaySettings(Integer.parseInt(getProperties().getProperty("switchg_time","5")));
    	
    	try {
    		byte[] disp_data = DispayUtil.from_cirilic_to_latinic_byte(_current_display);
    		disp_sett.addForDisplay(DisplaySettings.DISPLAY_BACK_KEY, disp_data);
    		disp_sett.addForDisplay(DisplaySettings.DISPLAY_FRONT_KEY, disp_data);
    	}catch(Exception e) {
    		System.out.println("Exception when try to prepar data for display, details: " + e.getMessage());
    	}
    	
    	
    	return disp_sett.getForDisplays();
    }

}

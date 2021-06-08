package application;
	
import application.util.AbstractLineColleaction;
import application.util.InputFileReader;
import application.util.LineWithNumberCollection;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.stage.Stage;
import javafx.stage.StageStyle;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.layout.BorderPane;


public class Main extends Application {
	
	
	@Override
	public void start(Stage primaryStage) {
		try {
			AbstractLineColleaction collection = InputFileReader.getCollection();
			
			String resource_view = (collection instanceof LineWithNumberCollection) ? "MainUI.fxml" : "NoLineNumUI.fxml";
			
			primaryStage.initStyle(StageStyle.UNDECORATED);
			//BorderPane root = new BorderPane();
			Parent root = FXMLLoader.load(getClass().getResource(resource_view));
			//Scene scene = new Scene(root,400,400);
			Scene scene = new Scene(root);
			String css = (collection instanceof LineWithNumberCollection) ? "/application/Main.css" : "/application/NoLineNum.css";
			scene.getStylesheets().add(css);
			primaryStage.setTitle("Бирање линије");
			primaryStage.setScene(scene);
			primaryStage.show();
		} catch(Exception e) {
			e.printStackTrace();
		}
	}
	
	public static void main(String[] args) {
		launch(args);
	}
}

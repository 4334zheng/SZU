public class shapeFactory {
    static public shape createShape(String name) throws UnsupportedShapeException{
        name = name.toLowerCase();
        shape res;
        switch (name){
            case "circle":
                res = new Circle();
                break;
            case "triangle":
                res = new Triangle();
                break;
            case "rectangle":
                res = new Rectangle();
                break;
            default:
                throw new UnsupportedShapeException();
        }
        return res;
    }
}


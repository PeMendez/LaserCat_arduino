import axios from "axios";

const moveApi = axios.create({
  baseURL: "http://192.168.1.1/move",
});

export const moveRandom = async () => {
    try {
      const response = await moveApi.post("/random");
      console.log("Mover random ok:", response.data);
      return response;
    } catch (error) {
      console.error("Error al mover:", error.message);
      throw error; 
    }
  };

export const moveUp = async () => {
  try {
    const response = await moveApi.post("/up");
    console.log("Mover hacia arriba ok:", response.data);
    return response;
  } catch (error) {
    console.error("Error al mover:", error.message);
    throw error; 
  }
};

export const moveDown = async () => {
  try {
    const response = await moveApi.post("/down");
    console.log("Mover hacia abajo ok:", response.data);
    return response;
  } catch (error) {
    console.error("Error al mover:", error.message);
    throw error; 
  }
};

export const moveLeft = async () => {
  try {
    const response = await moveApi.post("/left");
    console.log("Mover hacia la izquierda ok:", response.data);
    return response;
  } catch (error) {
    console.error("Error al mover:", error.message);
    throw error; 
  }
};

export const moveRight = async () => {
  try {
    const response = await moveApi.post("/right");
    console.log("Mover hacia la derecha ok:", response.data);
    return response;
  } catch (error) {
    console.error("Error al mover:", error.message);
    throw error; 
  }
};

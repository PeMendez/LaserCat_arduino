import axios from "axios";

const configApi = axios.create({
  baseURL: "http://192.168.1.1/config",
});

export const configureLaser = async () => {
  try {
    const response = await configApi.post("/laser");
    console.log("Configuración del láser exitosa:", response.data);
    return response;
  } catch (error) {
    console.error("Error al configurar el láser:", error.message);
    throw error; 
  }
};

export const configureAutoplay = async () => {
  try {
    const response = await configApi.post("/autoplay");
    console.log("Configuración del autoplay exitosa:", response.data);
    return response;
  } catch (error) {
    console.error("Error al configurar el autoplay:", error.message);
    throw error;
  }
};

export const configSpeedUp = async () => {
  try {
    const response = await configApi.post("/autoplay/speedup"); 
    console.log("Configuración de subir la velocidad exitosa:", response.data);
    return response;
  } catch (error) {
    console.error("Error al configurar la velocidad:", error.message);
    throw error;
  }
}

export const configSpeedDown = async () => {
  try {
    const response = await configApi.post("/autoplay/speeddown"); 
    console.log("Configuración de bajar la velocidad exitosa:", response.data);
    return response;
  } catch (error) {
    console.error("Error al configurar la velocidad:", error.message);
    throw error;
  }
}

export const configAreaIncrease = async () => {
  try {
    const response = await configApi.post("/area/increase"); 
    console.log("Configuración para aumentar el área exitosa:", response.data);
    return response;
  } catch (error) {
    console.error("Error al configurar el área:", error.message);
    throw error;
  }
}

export const configAreaDecrease = async () => {
  try {
    const response = await configApi.post("/area/decrease"); 
    console.log("Configuración para decrementar el área exitosa:", response.data);
    return response;
  } catch (error) {
    console.error("Error al configurar el área:", error.message);
    throw error;
  }
}


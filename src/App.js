import React from 'react';
import Button from 'react-bootstrap/Button'
import './App.css'; 
import {
  configureLaser,
  configureAutoplay,
  configSpeedUp,
  configSpeedDown,
  configAreaIncrease,
  configAreaDecrease,
} from './services/configQueries'; 
import {
  moveRandom,
  moveUp,
  moveDown,
  moveLeft,
  moveRight,
} from './services/moveQueries'; 

const App = () => {
  return (
    <div className='home-container container'>
      <div className='container'>
        <h1 className='tittle-main'>
          <span className="title-text">Láser para gatos </span>
        </h1>
      </div>
      <div className='tittle'>
        <div><h1><span className="subtitle-text">Configuración</span></h1></div>
        <div><h1><span className="subtitle-text">Movimientos</span></h1></div>
      </div>
      <div className= 'table-button'>
        <div className='button-game mb-1'>
          <Button className='mb-4 info' variant="outline-info" onClick={configureLaser}>Configurar Láser</Button>
          <Button className='mb-4 info' variant="outline-info" onClick={configureAutoplay}>Autoplay</Button>
        <div className='categoria'>
          <h6><span className="subtitle-text color-sub">Velocidad</span></h6>
        </div>
          <Button className='mb-4 info' variant="outline-info" onClick={configSpeedUp}>Aumentar</Button>
          <Button className='mb-4 info' variant="outline-info" onClick={configSpeedDown}>Decrementar</Button>
        <div className='categoria'>
          <div><h6><span className="subtitle-text color-sub">Área</span></h6></div>
        </div>
          <Button className='mb-4 info' variant="outline-info" onClick={configAreaIncrease}>Aumentar</Button>
          <Button className='mb-4 info' variant="outline-info" onClick={configAreaDecrease}>Decrementar</Button>
        </div> 
        <div className='button-game mb-1'>
          <Button className='mb-4 outline-custom' onClick={moveRight}>Derecha</Button>
          <Button className='mb-4 outline-custom' onClick={moveLeft}>Izquierda</Button>
          <div>
          <Button className='mb-4 outline-custom' onClick={moveUp}>Arriba</Button>
          <Button className='mb-4 outline-custom' onClick={moveDown}>Abajo</Button>
          </div>
          <div className='categoria'>
          <Button className='mb-4 outline-custom' onClick={moveRandom}>Random</Button>
          </div>
        </div>  
      </div>                
    </div>
  );  
}

export default App;

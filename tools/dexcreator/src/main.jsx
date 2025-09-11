import { StrictMode } from 'react'
import { createRoot } from 'react-dom/client'
import './index.css'
import PokedexApp from "./components/PokedexApp.jsx";

createRoot(document.getElementById('root')).render(
  <StrictMode>
    <PokedexApp />
  </StrictMode>,
)

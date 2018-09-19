using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Entidades
{
    public enum EMarcaProducto
    {
        Manaos,Pitusas,Naranjú,Diversión,Swift,Favorita
    }

    public enum ETipoProducto
    {
        Galletita, Gaseosa, Jugo, Harina, Todos
    }

    public abstract class Producto
    {
        #region Atributos
        protected int _codigoBarra;
        protected EMarcaProducto _marca;
        protected float _precio;
        #endregion

        #region Propiedades
        public float CalcularCostoDeProduccion { get; }

        public EMarcaProducto Marca
        {
            get
            {
                return this._marca;
            }
        }

        public float Precio
        {
            get
            {
                return this._precio;
            }
        }
        #endregion

        #region Constructor
        public Producto(int codigoBarra, EMarcaProducto marca, float precio)
        {
            this._codigoBarra = codigoBarra;
            this._marca = marca;
            this._precio = precio;
        }
        #endregion

        #region Métodos
        public string Consumir()
        {

        }

        protected string MostrarProducto(Producto p)
        {

        }
        #endregion

        #region Sobrecargas
        public override bool Equals(object obj)
        {

        }

        public static explicit operator int(Producto p)
        {

        }

        public static implicit operator string(Producto p)
        {

        }

        public static bool operator ==(Producto proUno, EMarcaProducto marca)
        {

        }

        public static bool operator ==(Producto proUno, Producto proDos)
        {

        }

        public static bool operator ==(Producto proUno, EMarcaProducto marca)
        {

        }

        public static bool operator ==(Producto proUno, Producto proDos)
        {

        }
        #endregion
    }
}

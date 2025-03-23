using DataVista.Database.Interface;
using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data.SqlClient;
using System.Management;

namespace DataVista.Database
{
    public class dvConnection : IdvConnection, IDisposable
    {
        #region FIELDS
        private bool _disposed = false;
        private SqlConnection? _sqlConnection;

        /// <summary>
        /// Configured using <see cref="ConfigurationManager"/>
        /// </summary>
        private string _connectionString = ConfigurationManager.ConnectionStrings["DbConnectionString"].ConnectionString;
        #endregion

        #region CONSTRUCTOR & DESTRUCTOR
        /// <summary>
        /// Inject your own initialized sqlConnection into this constructor.
        /// </summary>
        /// <param name="sqlConnection"></param>
        /// <exception cref="DataException"></exception>
        public dvConnection(SqlConnection sqlConnection)
        {
            if (_sqlConnection == null)
            {
                _sqlConnection = sqlConnection;
            }
            else
            {
                throw new DataException($"{this} failed to build ConnectionString");
            }
        }

        /// <summary>
        /// Pass a valid connectionString into this constructor.
        /// </summary>
        /// <param name="connectionString"></param>
        public dvConnection(string connectionString)
        {
            if (_sqlConnection == null)
            {
                _sqlConnection = new SqlConnection(connectionString);
            }
        }

        /// <summary>
        /// Destructor required to make the <see cref="dvConnection"/> of type <see cref="IDisposable"./>
        /// </summary>
        ~dvConnection()
        {
            _disposed = true;

            if (_sqlConnection != null)
            {
                _sqlConnection.Dispose();
            }

            Dispose(true);
        }
        #endregion

        #region PROPERTIES
        public string ConnectionString
        {
            get { return _connectionString; }
        }

        /// <summary>
        /// Returns a string that identifies the database client.
        /// Similar behaviour to EnvironmentUserName.
        /// </summary>
        public string WorkstationId
        {
            get
            {
                if (_sqlConnection != null) return _sqlConnection.WorkstationId;
                else return "this.SqlConnection == null";
            }
        }

        public SqlConnection SqlConnection
        {
            get
            {
                if (_sqlConnection != null) return _sqlConnection;
                else return null;
            }
        }

        public ConnectionState ConnectionState
        {
            get
            {
                if (_sqlConnection != null) return _sqlConnection.State;
                else return ConnectionState.Closed;
            }
            set
            {
                if (_sqlConnection != null)
                {
                    if (_sqlConnection.State != value)
                    {
                        if (value == ConnectionState.Open)
                        {
                            _sqlConnection.Open();
                        }
                    }
                    else
                    {
                        if (_sqlConnection.State == ConnectionState.Closed)
                        {
                            _sqlConnection.Close();
                        }
                    }
                }
            }
        }

        /// <summary>
        /// Returns a connection ID of the most recent connection attempt,
        /// regardless of whether the attempt succeeded or failed.
        /// </summary>
        public Guid ConnectionId
        {
            get
            {
                if (_sqlConnection != null) return _sqlConnection.ClientConnectionId;
                else return Guid.Empty;
            }
        }
        #endregion

        #region METHODS
        public void Dispose()
        {
            _disposed = true;
            GC.SuppressFinalize(this);
        }

        protected virtual void Dispose(bool disposing)
        {
            if (!_disposed)
            {
                if (disposing)
                {
                    if (_sqlConnection != null)
                    {
                        _sqlConnection.Dispose();
                        _sqlConnection = null;
                    }
                }
                _disposed = true;
            }
        }

        public override string ToString()
        {
            string connection = $"Connection is {ConnectionState}.";

            return connection;
        }
        #endregion
    }
}
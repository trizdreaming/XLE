﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace ControlsLibrary
{
    public partial class InvalidAssetDialog : Form
    {
        public InvalidAssetDialog()
        {
            InitializeComponent();

            _list = new GUILayer.InvalidAssetList();
            _assetList.Items.Clear();
            foreach (var a in _list.AssetList)
                _assetList.Items.Add(a.Item1);

            _assetList.SelectedIndexChanged += SelectedIndexChanged;
        }

        void SelectedIndexChanged(object sender, EventArgs e)
        {
            _errorDetails.Clear();
            foreach (var a in _list.AssetList)
                if (a.Item1.Equals(_assetList.SelectedItem))
                    _errorDetails.Text = a.Item2;
        }

        protected GUILayer.InvalidAssetList _list;
    }
}
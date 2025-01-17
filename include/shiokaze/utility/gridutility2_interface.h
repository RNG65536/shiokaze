/*
**	gridutility2_interface.h
**
**	This is part of Shiokaze, a research-oriented fluid solver for computer graphics.
**	Created by Ryoichi Ando <rand@nii.ac.jp> on July 15, 2017. 
**
**	Permission is hereby granted, free of charge, to any person obtaining a copy of
**	this software and associated documentation files (the "Software"), to deal in
**	the Software without restriction, including without limitation the rights to use,
**	copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the
**	Software, and to permit persons to whom the Software is furnished to do so,
**	subject to the following conditions:
**
**	The above copyright notice and this permission notice shall be included in all copies
**	or substantial portions of the Software.
**
**	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
**	INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
**	PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
**	HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
**	CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
**	OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
//
#ifndef SHKZ_GRIDUTILITY2_INTERFACE_H
#define SHKZ_GRIDUTILITY2_INTERFACE_H
//
#include <shiokaze/core/recursive_configurable_module.h>
#include <shiokaze/array/array2.h>
//
SHKZ_BEGIN_NAMESPACE
//
/** @file */
/// \~english @brief Interface for handling grid related operations. "gridutility2" is provided as implementation.
/// \~japanese @brief グリッドの関係する操作を処理するインターフェース。"gridutility2" が実装として提供される。
class gridutility2_interface : public recursive_configurable_module {
public:
	//
	DEFINE_MODULE(gridutility2_interface,"Grid Utility 2D","GridUtility","Grid utility module")
	/**
	 \~english @brief Convert a nodal grid to a cell-centered grid.
	 @param[in] nodal_array Nodal grid.
	 @param[out] result Resulting cell-based array.
	 \~japanese @brief ノードベースのグリッドをセルベースのグリッドに変換する。
	 @param[in] nodal_array ノードベースのグリッド。
	 @param[out] result 結果のセルベースのグリッド。
	 */
	virtual void convert_to_cell( const array2<float> &nodal_array, array2<float> &result ) const = 0;
	/**
	 \~english @brief Enclose a fluid level set by solid.
	 @param[in] solid Solid level set.
	 @param[in] fluid Fluid level set.
	 @param[out] combined Encapsulated level set.
	 @param[in] solid_offset Offset of the solid level set.
	 \~japanese @brief 流体のレベルセットを壁のレベルセットで包む。
	 @param[in] solid 壁のレベルセット。
	 @param[in] fluid 流体のレベルセット。
	 @param[out] combined 包まれた結果のレベルセット。
	 @param[in] solid_offset 壁のレベルセットのオフセット。
	 */
	virtual void combine_levelset( const array2<float> &solid, const array2<float> &fluid, array2<float> &combined, double solid_offset=0.0 ) const = 0;
	/**
	 \~english @brief Extrapolate fluid level set towards solid.
	 @param[in] solid Solid level set.
	 @param[in-out] fluid level set to extrapolate.
	 @param[in] threshold Solid level set isocontour.
	 \~japanese @brief 流体のレベルセットを壁の方向へ外挿する。
	 @param[in] solid 壁のレベルセット。
	 @param[in-out] fluid 外挿する流体のレベルセット。
	 @param[in] threshold 壁のレベルセットの表面のレベルセットの値。
	 */
	virtual void extrapolate_levelset( const array2<float> &solid, array2<float> &fluid, double threshold=0.0 ) const = 0;
	/**
	 \~english @brief Compute the gradient of a level set.
	 @param[in] levelset Level set.
	 @param[out] gradient Output gradient.
	 \~japanese @brief レベルセットの勾配を計算する。
	 @param[in] levelset レベルセット。
	 @param[out] gradient 出力の勾配。
	 */
	virtual void compute_gradient( const array2<float> &levelset, array2<vec2f> &gradient ) const = 0;
	/**
	 \~english @brief Trim narrow band of a level set within one cell away from the interface.
	 @param[in] levelset Fluid level set.
	 \~japanese @brief レベルセットを境界から1セルだけ離れたセルにトリミングする。
	 @param[in] levelset 流体のレベルセット。
	 */
	virtual void trim_narrowband( array2<float> &levelset ) const = 0;
	/**
	 \~english @brief Get the area of fluid level set.
	 @param[in] solid Solid level set.
	 @param[in] fluid Fluid level set.
	 @return Area.
	 \~japanese @brief レベルセットの面積を計算する。
	 @param[in] solid 壁のレベルセット。
	 @param[in] fluid 流体のレベルセット。
	 @return 面積。
	 */
	virtual double get_area( const array2<float> &solid, const array2<float> &fluid ) const = 0;
	//
private:
	virtual void initialize( const shape2 &shape, double dx ) = 0;
	virtual void initialize( const configurable::environment_map &environment ) override {
		//
		assert(check_set(environment,{"shape","dx"}));
		initialize(
			get_env<shape2>(environment,"shape"),
			get_env<double>(environment,"dx")
		);
	}
};
//
using gridutility2_ptr = std::unique_ptr<gridutility2_interface>;
using gridutility2_driver = recursive_configurable_driver<gridutility2_interface>;
//
SHKZ_END_NAMESPACE
//
#endif
//